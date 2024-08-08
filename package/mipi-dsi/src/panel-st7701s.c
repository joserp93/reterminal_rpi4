// SPDX-License-Identifier: GPL-2.0+
/*
 * ST7701s panel driver
 * 
 * Copyright (c) 2020 Seeed Studio
 * Zhangqun Ming<north_sea@qq.com>
 */
#include "mipi_dsi.h"


static struct mipi_dsi_device *st7701s_dsi = NULL;

static const struct drm_display_mode st7701s_modes[] = {
	{
		.clock		= /*27500*/28748,

		.hdisplay	= 480,
		.hsync_start	= 480 + 38,
		.hsync_end	= 480 + 38 + 12,
		.htotal		= 480 + 38 + 12 + 12,

		.vdisplay	= 854,
		.vsync_start	= 854 + 18,
		.vsync_end	= 854 + 18 + 8,
		.vtotal		= 854 + 18 + 8 + 4,
	},
};

static int st7701s_get_modes(struct drm_panel *panel, struct drm_connector *connector)
{
	unsigned int i, num = 0;
	static const u32 bus_format = MEDIA_BUS_FMT_RGB888_1X24;

	for (i = 0; i < ARRAY_SIZE(st7701s_modes); i++) {
		const struct drm_display_mode *m = &st7701s_modes[i];
		struct drm_display_mode *mode;

		mode = drm_mode_duplicate(connector->dev, m);
		if (!mode) {
			dev_err(panel->dev, "failed to add mode %ux%u@%u\n",
				m->hdisplay, m->vdisplay,
				drm_mode_vrefresh(m));
			continue;
		}

		mode->type |= DRM_MODE_TYPE_DRIVER;
		if (i == 0)
			mode->type |= DRM_MODE_TYPE_PREFERRED;

		drm_mode_set_name(mode);
		drm_mode_probed_add(connector, mode);
		num++;
	}

	connector->display_info.bpc = 8;
	connector->display_info.width_mm = 62;
	connector->display_info.height_mm = 110;
	drm_display_info_set_bus_formats(&connector->display_info, &bus_format, 1);

	return num;
}

static int st7701s_prepare(struct drm_panel *panel)
{
	struct mipi_dsi_device *dsi = st7701s_dsi;

	if (!dsi)
		return -1;

	DBG_FUNC();
	
	DSI_DCS_WRITE(dsi, 0x11);
	msleep(50);
	DSI_DCS_WRITE(dsi, 0xFF, 0x77,0x01,0x00,0x00,0x10);
	DSI_DCS_WRITE(dsi, 0xC0, 0xE9,0x03);
	DSI_DCS_WRITE(dsi, 0xC1, 0x0A,0x02);
	DSI_DCS_WRITE(dsi, 0xC2, 0x01,0x06);
	DSI_DCS_WRITE(dsi, 0xCC, 0x10);
	DSI_DCS_WRITE(dsi, 0xB0, 0x00,0x12,0x1A,0x0D,0x11,0x07,0x0C,0x0A,0x09,0x26,0x05,0x11,0x10,0x2B,0x33,0x1B);
	DSI_DCS_WRITE(dsi, 0xB1, 0x00,0x12,0x1A,0x0D,0x11,0x06,0x0B,0x07,0x08,0x26,0x03,0x11,0x0F,0x2B,0x33,0x1B);
	DSI_DCS_WRITE(dsi, 0xFF, 0x77,0x01,0x00,0x00,0x11);
	DSI_DCS_WRITE(dsi, 0xB0, 0x4D);
	DSI_DCS_WRITE(dsi, 0xB1, 0x2C);
	DSI_DCS_WRITE(dsi, 0xB2, 0x87);
	DSI_DCS_WRITE(dsi, 0xB3, 0x80);
	DSI_DCS_WRITE(dsi, 0xB5, 0x40);
	DSI_DCS_WRITE(dsi, 0xB7, 0x85);
	DSI_DCS_WRITE(dsi, 0xB8, 0x21);
	DSI_DCS_WRITE(dsi, 0xB9, 0x10);
	DSI_DCS_WRITE(dsi, 0xC0, 0x03);
	DSI_DCS_WRITE(dsi, 0xC1, 0x78);
	DSI_DCS_WRITE(dsi, 0xC2, 0x78);
	DSI_DCS_WRITE(dsi, 0xD0, 0x88);
	msleep(100);
	DSI_DCS_WRITE(dsi, 0xE0, 0x00,0x00,0x02);
	DSI_DCS_WRITE(dsi, 0xE1, 0x04,0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x00,0x20,0x20);
	DSI_DCS_WRITE(dsi, 0xE2, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
	DSI_DCS_WRITE(dsi, 0xE3, 0x00,0x00,0x33,0x00);
	DSI_DCS_WRITE(dsi, 0xE4, 0x22, 0x00);
	DSI_DCS_WRITE(dsi, 0xE5, 0x04,0x5C,0xA0,0xA0,0x06,0x5C,0xA0,0xA0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
	DSI_DCS_WRITE(dsi, 0xE6, 0x00,0x00,0x33,0x00);
	DSI_DCS_WRITE(dsi, 0xE7, 0x22, 0x00);
	DSI_DCS_WRITE(dsi, 0xE8, 0x05,0x5C,0xA0,0xA0,0x07,0x5C,0xA0,0xA0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
	DSI_DCS_WRITE(dsi, 0xEB, 0x02,0x00,0x40,0x40,0x00,0x00,0x00);
	DSI_DCS_WRITE(dsi, 0xEC, 0x00, 0x00);
	DSI_DCS_WRITE(dsi, 0xED, 0xFA,0x45,0x0B,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xB0,0x54,0xAF);
	DSI_DCS_WRITE(dsi, 0xFF, 0x77,0x01,0x00,0x00,0x00);

#if 0
	DSI_DCS_WRITE(dsi, 0xff, 0x77, 0x01, 0x00, 0x00, 0x12);
	DSI_DCS_WRITE(dsi, 0xD1, 0x81,0x20,0x03,0x56,0x08,0x01,0xC0,0x01,0xE0,0xC0,0x01,0xE0,0x03,0x56);//854
	DSI_DCS_WRITE(dsi, 0xD2, 0x06);//选择图片彩条画面（图片表格从左上角开始0x00，最右下角0x0f)
#endif

	DSI_DCS_WRITE(dsi, 0x29);

	return 0;
}

static const struct drm_panel_funcs st7701s_funcs = {
	.get_modes = st7701s_get_modes,
	.prepare = st7701s_prepare,
};

static void st7701s_set_dsi(struct mipi_dsi_device *dsi)
{
	st7701s_dsi = dsi;
	dsi->mode_flags = (MIPI_DSI_MODE_LPM | MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_SYNC_PULSE);
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->lanes = 1;
}

const struct panel_data st7701s_data = {
	.set_dsi = st7701s_set_dsi,
	.funcs = &st7701s_funcs,
};
