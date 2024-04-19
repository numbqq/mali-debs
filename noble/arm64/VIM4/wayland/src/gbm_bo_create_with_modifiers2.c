#include <stdbool.h>
#include <libdrm/drm_fourcc.h>
#include "gbm.h"

struct gbm_bo *
gbm_bo_create_with_modifiers2(struct gbm_device *gbm,
                              uint32_t width, uint32_t height,
                              uint32_t format,
                              const uint64_t *modifiers,
                              const unsigned int count,
                              uint32_t flags)
{
	struct gbm_bo *gbm_bo;

	gbm_bo = gbm_bo_create_with_modifiers (gbm,
                                              width, height, format,
                                              modifiers, count);

	if (!gbm_bo)
	{
		bool has_mod_invalid = false, has_mod_linear = false;
		int i;

		for (i = 0; i < count; i++) {
			if (modifiers[i] == DRM_FORMAT_MOD_INVALID)
				has_mod_invalid = true;
			else if (modifiers[i] == DRM_FORMAT_MOD_LINEAR)
				has_mod_linear = true;
		}

		if (!has_mod_invalid && has_mod_linear)
			flags |= GBM_BO_USE_LINEAR;

		gbm_bo = gbm_bo_create(gbm, width, height, format, flags);
	}

	return gbm_bo;
}
