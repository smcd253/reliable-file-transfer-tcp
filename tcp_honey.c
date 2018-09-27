/*
	TCP Honey Congestion Control
*/

#include <linux/mm.h>
#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/inet_diag.h>
#include <linux/printk.h>
#include <net/tcp.h>

struct honey{
	bool	honey_en;
	bool	if_congested;
	u32		rtt_min;
	u32		rtt;
};

#define TCP_HONEY_INIT_RTT 1000000 /* 1 sec */

static void tcp_honey_init(struct sock *sk)
{
	
	struct honey *honey = inet_csk_ca(sk);
	printk(KERN_DEBUG "tcp_honey_init--------start\n");

	honey->honey_en = true;
	honey->if_congested = false;
	honey->rtt_min = TCP_HONEY_INIT_RTT;
	honey->rtt = TCP_HONEY_INIT_RTT;
	printk(KERN_DEBUG "tcp_honey_init--------end\n");
}

static void tcp_honey_pkts_acked(struct sock *sk, u32 cnt, s32 rtt_us)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct honey *honey = inet_csk_ca(sk);
	// printk(KERN_DEBUG "tcp_honey_pkts_acked--------start\n");

	printk(KERN_DEBUG "theshold size in packack: %d\n", tp->snd_ssthresh);

	if (rtt_us > 0)
		honey->rtt = rtt_us;
	honey->rtt_min = min(honey->rtt_min, honey->rtt);
	printk(KERN_DEBUG "honey window size in packack: %d\n", tp->snd_cwnd);
	
	tp->snd_cwnd = 65000;
	// printk(KERN_DEBUG "tcp_honey_pkts_acked--------end\n");
}

static u32 tcp_honey_undo_cwnd(struct sock *sk) {
	printk(KERN_DEBUG "undo_cwnd............\n");
	printk(KERN_DEBUG "honey window size: %d\n", ((struct tcp_sock *)tcp_sk(sk))->snd_cwnd);
	return 65000;
}

static void tcp_honey_state(struct sock *sk, u8 ca_state)
{
	
	struct honey *honey = inet_csk_ca(sk);
	printk(KERN_DEBUG "tcp_honey_state--------start\n");

	// honey->honey_en = (ca_state == TCP_CA_Open);
	honey->honey_en = true;

	// printk(KERN_DEBUG " state = %d\n", ca_state);
	printk(KERN_DEBUG "honey window size after state %d: %d\n", ca_state, ((struct tcp_sock *)tcp_sk(sk))->snd_cwnd);
	printk(KERN_DEBUG "tcp_honey_state--------end\n");

}

/* estimate if this is a congestion loss */
static void tcp_honey_congestion_det(struct honey *honey)
{
	printk(KERN_DEBUG "tcp_honey_congestion_det--------start\n");
	honey->if_congested = (honey->rtt > honey->rtt_min << 1U);
	printk(KERN_DEBUG "tcp_honey_congestion_det--------end\n");
}

static void tcp_honey_cwnd_event(struct sock *sk, enum tcp_ca_event event)
{
	struct tcp_sock *tp = tcp_sk(sk);
	printk(KERN_DEBUG "tcp_honey_cwnd_event--------start\n");
	// struct honey *honey = inet_csk_ca(sk);

	printk(KERN_DEBUG "EVENT : %d\n", event);
	printk(KERN_DEBUG "honey window size: %d\n", tp->snd_cwnd);

	tp->snd_cwnd = 65000;
	printk(KERN_DEBUG "honey window size: %d\n", tp->snd_cwnd);

	// switch (event) {
	// 	case CA_EVENT_LOSS:
	// 		tp->snd_cwnd = 50000;
	// 		printk(KERN_DEBUG "in event loss\n");
	// 		break;
	// 	default:
	// 		//don't care
	// 		break;
	// }
	printk(KERN_DEBUG "tcp_honey_cwnd_event--------end\n");
}

static void tcp_honey_cong_avoid(struct sock *sk, u32 ack, u32 acked)
{
	
	struct tcp_sock *tp = tcp_sk(sk);
	struct honey *honey = inet_csk_ca(sk);
	u32 inc;

	printk(KERN_DEBUG "tcp_honey_cong_avoid--------start\n");

	printk(KERN_DEBUG "honey window size: %d\n", tp->snd_cwnd);

	if (!honey->honey_en) {
		tcp_reno_cong_avoid(sk, ack, acked);
		return;
	}

	tcp_honey_congestion_det(honey);
	/* limited by applications */
/*	if (!tcp_is_cwnd_limited(sk))
		return;
*/
	if (tcp_in_slow_start(tp)){
		/* in slow start, double send window*/
		printk(KERN_DEBUG "tcp is in slow start\n");
		inc = tp->snd_cwnd;
	} else {
		/* congestion avoidance */
		printk(KERN_DEBUG "tcp is NOT in slow start\n");
		inc = 1;
	}
	printk(KERN_DEBUG "honey window size: %d\n", tp->snd_cwnd);

	if ((tp->snd_cwnd >> 1U) + (inc >> 1U) > (tp->snd_cwnd_clamp >> 1U)){
		tp->snd_cwnd = (tp->snd_cwnd >> 1U) + (tp->snd_cwnd_clamp >> 1u);
	} else {
		tp->snd_cwnd += inc;
	}
	tp->snd_cwnd = 65000;

	printk(KERN_DEBUG "honey window size : %d\n", tp->snd_cwnd);
	printk(KERN_DEBUG "slow start thresh : %d\n", tp->snd_ssthresh);
	printk(KERN_DEBUG "tcp_honey_cong_avoid--------end\n");
}

static u32 tcp_honey_ssthresh(struct sock *sk)
{
	
	// const struct tcp_sock *tp = tcp_sk(sk);
	struct honey *honey = inet_csk_ca(sk);

	if (honey->if_congested)
		return 65000;
	else
		return 65000;
}

static struct tcp_congestion_ops tcp_honey __read_mostly = {
	.init		= tcp_honey_init,
	.ssthresh	= tcp_honey_ssthresh,
	.cong_avoid	= tcp_honey_cong_avoid,
	.cwnd_event = tcp_honey_cwnd_event,
	.pkts_acked	= tcp_honey_pkts_acked,
	.set_state	= tcp_honey_state,
	.undo_cwnd	= tcp_honey_undo_cwnd,

	.owner		= THIS_MODULE,
	.name		= "honey",
};

static int __init tcp_honey_register(void)
{
	printk(KERN_DEBUG "tcp_honey_register--------start\n");
	BUILD_BUG_ON(sizeof(struct honey) > ICSK_CA_PRIV_SIZE);
	tcp_register_congestion_control(&tcp_honey);
	printk(KERN_DEBUG "tcp_honey_register--------end\n");
	return 0;
}

static void __exit tcp_honey_unregister(void)
{
	printk(KERN_DEBUG "tcp_honey_unregister--------start\n");
	tcp_unregister_congestion_control(&tcp_honey);
	printk(KERN_DEBUG "tcp_honey_unregister--------end\n");
}

module_init(tcp_honey_register);
module_exit(tcp_honey_unregister);

MODULE_AUTHOR("Cheng Qian");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("TCP Honey");