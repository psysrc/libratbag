#include "libratbag-private.h"

#define GXTRUST_NUM_PROFILES 4
#define GXTRUST_NUM_RESOLUTIONS 4

static int
gxtrust_probe(struct ratbag_device *device)
{
    log_debug(device->ratbag,
		"gxtrust: probe %04x:%04x (%s)\n",
		device->ids.vendor, device->ids.product,
		device->name);

	struct ratbag_profile *profile = NULL;
	struct ratbag_resolution *res = NULL;

	// How many profiles, DPI resolutions, buttons, and LEDs the mouse has
	ratbag_device_init_profiles(device, GXTRUST_NUM_PROFILES, GXTRUST_NUM_RESOLUTIONS, 1, 0);

	ratbag_device_for_each_profile(device, profile) {
		ratbag_profile_for_each_resolution(profile, res) {
			// Set dummy DPI range
			ratbag_resolution_set_dpi_list_from_range(res, 100, 2000);
			ratbag_resolution_set_resolution(res, 800, 800);

			unsigned int rates[] = { 500, 1000 };
			ratbag_profile_set_report_rate_list(profile, rates, ARRAY_LENGTH(rates));
		}

		res = ratbag_profile_get_resolution(profile, 0);
		if (!res) {
			log_error(device->ratbag,
				"gxtrust: failed to get resolution\n");
			return RATBAG_ERROR_IMPLEMENTATION;
		}
		res->is_active = true;
	}

	profile = ratbag_device_get_profile(device, 0);
	if (!profile) {
		log_error(device->ratbag,
			"gxtrust: failed to get profile\n");
		return RATBAG_ERROR_IMPLEMENTATION;
	}

	profile->is_active = true;

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
