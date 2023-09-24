/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _CPUFREQ_SCHEDUTIL_H_
#define _CPUFREQ_SCHEDUTIL_H_
#define IOWAIT_BOOST_MIN	(SCHED_CAPACITY_SCALE / 8)

struct sugov_tunables {
	struct gov_attr_set	attr_set;
	unsigned int		rate_limit_us;
	bool				cobuck_enable;
#ifdef CONFIG_OPLUS_UAG_AMU_AWARE
	bool				stall_aware;
	u64				stall_reduce_pct;
	int				report_policy;
#endif
};

struct sugov_policy {
	struct cpufreq_policy	*policy;

	struct sugov_tunables	*tunables;
	struct list_head	tunables_hook;

	raw_spinlock_t		update_lock;	/* For shared policies */
	u64			last_freq_update_time;
	s64			freq_update_delay_ns;
	unsigned int		next_freq;
	unsigned int		cached_raw_freq;

	/* The next fields are only needed if fast switch cannot be used: */
	struct			irq_work irq_work;
	struct			kthread_work work;
	struct			mutex work_lock;
	struct			kthread_worker worker;
	struct task_struct	*thread;
	bool			work_in_progress;

	bool			limits_changed;
	bool			need_freq_update;
	bool			cobuck_boosted;

	unsigned int		len;
};

#define MAX_CLUSTERS 3
static int init_flag[MAX_CLUSTERS];

#endif /* _CPUFREQ_SCHEDUTIL_H_ */
