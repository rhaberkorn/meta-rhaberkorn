DESCRIPTION = "Advanced TECO dialect and interactive screen editor based on Scintilla"
HOMEPAGE = "http://sciteco.sf.net/"
SECTION = "console/utils"

LICENSE = "GPL-3.0-only"
LIC_FILES_CHKSUM = "file://COPYING;md5=d32239bcb673463ab874e80d47fae504"

PR = "r0"

SRC_URI = "gitsm://github.com/rhaberkorn/sciteco.git;protocol=https;branch=master"

S = "${WORKDIR}/git"

# SciTECO does not support out-of-tree builds out of the box since
# Scintilla doesn't.
inherit autotools-brokensep pkgconfig

# Since we are cross-compiling, bootstrapping cannot work.
# Instead there must be a native sciteco available.
# The native SciTECO is always built with bootstrapping and
# the target SciTECO without.
BBCLASSEXTEND = "native"
EXTRA_OECONF:class-native = "--with-interface=ncurses --enable-bootstrap"
EXTRA_OECONF:class-target = "--with-interface=ncurses --disable-bootstrap"

DEPENDS:class-native = "pkgconfig-native ncurses-native glib-2.0-native groff-native"
DEPENDS:class-target = "sciteco-curses-native ncurses glib-2.0 groff-native"
RDEPENDS:${PN}:class-target = "ncurses-terminfo"

PACKAGECONFIG ??= "lexilla malloc-replacement"

PACKAGECONFIG[lexilla] = ",--without-lexilla"
PACKAGECONFIG[malloc-replacement] = ",--disable-malloc-replacement"
PACKAGECONFIG[teco-integer-32] = "--with-teco-integer=32"

# LTO will also decrease binary size.
# On the downside, LTO breaks debugging.
# Once there is a site-config option, it should go into PACKAGECONFIG.
PACKAGECONFIG[lto] = ""
CFLAGS += "${@bb.utils.contains('PACKAGECONFIG', 'lto', '-flto', '', d)}"
CXXFLAGS += "${@bb.utils.contains('PACKAGECONFIG', 'lto', '-flto', '', d)}"
LDFLAGS += "${@bb.utils.contains('PACKAGECONFIG', 'lto', '-flto', '', d)}"

FILES:${PN} += "${datadir}/sciteco"

# Woman pages also do not have to be installed by default
FILES:${PN}-doc += " \
	${bindir}/tedoc.tes ${bindir}/grosciteco.tes \
	${datadir}/sciteco/lib/lexers/woman.tes ${datadir}/sciteco/lib/women \
"

# Factor out the icons into a separate package.
# We usually don't need them.
PACKAGES =+ "${PN}-icons"
FILES:${PN}-icons = "${datadir}/sciteco/*.png"
