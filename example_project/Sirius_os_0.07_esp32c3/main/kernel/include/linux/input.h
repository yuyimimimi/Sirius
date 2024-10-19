#ifndef _LINUX_INPUT_H
#define _LINUX_INPUT_H

#include <linux/types.h>
#include <linux/list.h>
#include <time.h>

#define EV_CNT 32  
#define REL_CNT 16  
#define ABS_CNT 32  
#define MSC_CNT 16  
#define LED_CNT 32  
#define SND_CNT 16  
#define SW_CNT 16  
#define KEY_CNT 256  
#define REP_CNT 2  
#define FF_CNT 10  

#define MAX_NAME_LEN 256  
#define INPUT_PROP_CNT 32  
#define INPUT_PROP_POINTER 0x00000001  
#define INPUT_PROP_DIRECT 0x00000002  


#define BITS_TO_LONGS(bits) (((bits) + (sizeof(unsigned long) * 8) - 1) / (sizeof(unsigned long) * 8))

struct timer_list timer;
struct input_dev;


struct input_id {
    __u16 bustype;
    __u16 vendor;
    __u16 product;
    __u16 version;
};

struct input_value {
	__u16 type;
	__u16 code;
	__s32 value;
};

enum input_clock_type {
	INPUT_CLK_REAL = 0,
	INPUT_CLK_MONO,
	INPUT_CLK_BOOT,
	INPUT_CLK_MAX
};

struct input_value {
	__u16 type;
	__u16 code;
	__s32 value;
};


struct input_handle {

	void *private;

	int open;
	const char *name;

	struct input_dev *dev;
	struct input_handler *handler;

	struct list_head	d_node;
	struct list_head	h_node;
};



struct input_dev {
	const char *name;
	const char *phys;
	const char *uniq;
	struct input_id id;

	unsigned long propbit[BITS_TO_LONGS(INPUT_PROP_CNT)];

	unsigned long evbit[BITS_TO_LONGS(EV_CNT)];
	unsigned long keybit[BITS_TO_LONGS(KEY_CNT)];
	unsigned long relbit[BITS_TO_LONGS(REL_CNT)];
	unsigned long absbit[BITS_TO_LONGS(ABS_CNT)];
	unsigned long mscbit[BITS_TO_LONGS(MSC_CNT)];
	unsigned long ledbit[BITS_TO_LONGS(LED_CNT)];
	unsigned long sndbit[BITS_TO_LONGS(SND_CNT)];
	unsigned long ffbit[BITS_TO_LONGS(FF_CNT)];
	unsigned long swbit[BITS_TO_LONGS(SW_CNT)];

	unsigned int hint_events_per_packet;

	unsigned int keycodemax;
	unsigned int keycodesize;
	void *keycode;

	int (*setkeycode)(struct input_dev *dev,
			  const struct input_keymap_entry *ke,
			  unsigned int *old_keycode);
	int (*getkeycode)(struct input_dev *dev,
			  struct input_keymap_entry *ke);

	struct ff_device *ff;

	struct input_dev_poller *poller;

	unsigned int repeat_key;
	//struct timer_list timer;

	int rep[REP_CNT];

	struct input_mt *mt;

	struct input_absinfo *absinfo;

	unsigned long key[BITS_TO_LONGS(KEY_CNT)];
	unsigned long led[BITS_TO_LONGS(LED_CNT)];
	unsigned long snd[BITS_TO_LONGS(SND_CNT)];
	unsigned long sw[BITS_TO_LONGS(SW_CNT)];

	int (*open)(struct input_dev *dev);
	void (*close)(struct input_dev *dev);
	int (*flush)(struct input_dev *dev, struct file *file);
	int (*event)(struct input_dev *dev, unsigned int type, unsigned int code, int value);

	// struct input_handle __rcu *grab;

	// spinlock_t event_lock;
	// struct mutex mutex;

	unsigned int users;
	bool going_away;

	// struct device dev;

	struct list_head	h_list;
	struct list_head	node;

	unsigned int num_vals;
	unsigned int max_vals;
	struct input_value *vals;

	bool devres_managed;

	ktime_t timestamp[INPUT_CLK_MAX];

	bool inhibited;
};


#endif /* _LINUX_INPUT_H */
