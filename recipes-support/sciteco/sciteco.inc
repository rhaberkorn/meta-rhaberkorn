DESCRIPTION = "Advanced TECO dialect and interactive screen editor based on Scintilla"
HOMEPAGE = "http://sciteco.sf.net/"
SECTION = "console/utils"

LICENSE = "GPLv3"
LIC_FILES_CHKSUM = "file://COPYING;md5=d32239bcb673463ab874e80d47fae504"

PR = "r0"

# NOTE: SciTECO's repository uses submodules, therefore the submodule
# fetcher must be used.
SRC_URI = "gitsm://github.com/rhaberkorn/sciteco.git;protocol=https"

S = "${WORKDIR}/git"

# SciTECO does not support out-of-tree builds out of the box since
# Scintilla doesn't.
inherit autotools-brokensep

# Currently parallel builds are broken for SciTECO
PARALLEL_MAKE = ""

# Since we are cross-compiling, bootstrapping cannot work.
# Instead there must be a native sciteco available.
# The native SciTECO is always built with bootstrapping and
# the target SciTECO without.
BBCLASSEXTEND = "native"
EXTRA_OECONF_class-native = "--with-interface=ncurses --enable-bootstrap"
EXTRA_OECONF_class-target = "--with-interface=ncurses --disable-bootstrap"

DEPENDS_class-native = "pkgconfig-native ncurses-native glib-2.0-native"
DEPENDS_class-target = "sciteco-native pkgconfig ncurses glib-2.0"
RDEPENDS_${PN}_class-target = "ncurses-terminfo"

# In some versions of yocto, the gitsm fetcher is "broken" and does
# not fetch submodules recursively.
# Here's a workaround:
do_update_submodules() {
    git submodule update --init --recursive ${S}
}
addtask update_submodules after do_unpack before do_patch
