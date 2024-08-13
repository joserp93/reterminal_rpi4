################################################################################
#
# bq24179_charger
#
################################################################################

BQ24179_CHARGER_VERSION = 0.1
BQ24179_CHARGER_SITE = $(NERVES_DEFCONFIG_DIR)/package/bq24179_charger/src
BQ24179_CHARGER_SITE_METHOD = local# Other methods like git,wget,scp,file etc. are also available.

$(eval $(kernel-module))
$(eval $(generic-package))
