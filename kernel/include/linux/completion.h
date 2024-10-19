#ifndef _LINUX_COMPLETION_H
#define _LINUX_COMPLETION_H

// #include <linux/swait.h>
#include <stdio.h>

typedef struct completion {
	unsigned int done;
	// struct swait_queue_head wait;
};



#endif /* _LINUX_COMPLETION_H */