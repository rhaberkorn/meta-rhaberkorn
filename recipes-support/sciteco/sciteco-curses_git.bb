DEFAULT_PREFERENCE = "-1"

require sciteco-curses.inc

# The configuration for development HEAD commit builds.
# To use it add the following line to conf/local.conf:
#
# PREFERRED_VERSION_sciteco-curses-native = "git%"
# PREFERRED_VERSION_sciteco-curses = "git%"
#

# Use latest revision from branch specified in SRC_URI (master)
SRCREV = "${AUTOREV}"
# Makes sure that new commits result in new package versions:
PV = "git-${SRCPV}"
