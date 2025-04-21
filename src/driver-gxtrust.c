#include "libratbag-private.h"


static int
gxtrust_probe(struct ratbag_device *device)
{
    log_debug(device->ratbag,
		"gxtrust: probe %04x:%04x (%s)\n",
		device->ids.vendor, device->ids.product,
		device->name);

    return RATBAG_SUCCESS;
}

static void
gxtrust_remove(struct ratbag_device *device)
{
    log_info(device->ratbag,
		"gxtrust: remove %04x:%04x (%s)\n",
		device->ids.vendor, device->ids.product,
		device->name);
}

static int
gxtrust_commit(struct ratbag_device *device)
{
	log_info(device->ratbag,
		"gxtrust: commit %04x:%04x (%s)\n",
		device->ids.vendor, device->ids.product,
		device->name);

	return RATBAG_SUCCESS;
}

static int
gxtrust_set_current_profile(struct ratbag_device *device, unsigned int index)
{
	log_info(device->ratbag,
		"gxtrust: set profile %04x:%04x (%s)\n",
		device->ids.vendor, device->ids.product,
		device->name);

	return RATBAG_SUCCESS;
}

struct ratbag_driver gxtrust_driver = {
    .name   = "GXTrust Gaming Mice",
    .id     = "gxtrust",
    .probe  = gxtrust_probe,
    .remove = gxtrust_remove,
	.commit = gxtrust_commit,
	.set_active_profile = gxtrust_set_current_profile,
};
