DEFAULT_PREFERENCE = "-1"

require sciteco.inc

# The configuration for development HEAD commit builds.
# To use it add the following line to conf/local.conf:
#
# PREFERRED_VERSION_sciteco-native = "git%"
# PREFERRED_VERSION_sciteco = "git%"
#

# Use latest revision from branch specified in SRC_URI (master)
SRCREV = "${AUTOREV}"
# Makes sure that new commits result in new package versions:
PV = "git-${SRCPV}"

# Factor out the icons into a separate package.
# We usually don't need them.
PACKAGES =+ "${PN}-icons"
FILES_${PN}-icons = "${datadir}/${PN}/*.png"
