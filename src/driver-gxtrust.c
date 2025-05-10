#include "libratbag-private.h"


static int
gxtrust_probe(struct ratbag_device *device)
{
    log_debug(device->ratbag,
		"gxtrust: probe %04x:%04x (%s)\n",
		device->ids.vendor, device->ids.product,
		device->name);

	// Create 1 profile, 1 resolution, 1 button, 0 LEDs
	ratbag_device_init_profiles(device, 1, 1, 1, 0);

	struct ratbag_profile *profile = ratbag_device_get_profile(device, 0);
	profile->is_active = true;

	struct ratbag_resolution *res = ratbag_profile_get_resolution(profile, 0);
    res->is_active = true;

    // Set dummy DPI range
    ratbag_resolution_set_dpi_list_from_range(res, 100, 2000);
    ratbag_resolution_set_resolution(res, 800, 800);

	unsigned int rates[] = { 500, 1000 };
	ratbag_profile_set_report_rate_list(profile, rates, ARRAY_LENGTH(rates));

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
