################################################################################
#
# 
#
################################################################################

LIS3LV02D_VERSION = 0.1
LIS3LV02D_SITE = $(NERVES_DEFCONFIG_DIR)/package/lis3lv02d/src
LIS3LV02D_SITE_METHOD = local# Other methods like git,wget,scp,file etc. are also available.

$(eval $(kernel-module))
$(eval $(generic-package))
