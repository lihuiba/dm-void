#include <linux/device-mapper.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/bio.h>

#define DM_MSG_PREFIX "void"

static int void_ctr(struct dm_target *ti, unsigned int argc, char **argv)
{
	if (argc != 0) {
		ti->error = "No arguments required";
		return -EINVAL;
	}

	return 0;
}

static int void_map(struct dm_target *ti, struct bio *bio,
		      union map_info *map_context)
{
	bio_endio(bio, 0);
	return DM_MAPIO_SUBMITTED;
}

static struct target_type void_target = {
	.name   = "void",
	.version = {1, 1, 0},
	.module = THIS_MODULE,
	.ctr    = void_ctr,
	.map    = void_map,
};

static int __init dm_void_init(void)
{
	int r = dm_register_target(&void_target);

	if (r < 0)
		DMERR("register failed %d", r);

	return r;
}

static void __exit dm_void_exit(void)
{
	dm_unregister_target(&void_target);
}

module_init(dm_void_init)
module_exit(dm_void_exit)

MODULE_DESCRIPTION(DM_NAME " dummy target ignoring bios");
MODULE_LICENSE("GPL");
