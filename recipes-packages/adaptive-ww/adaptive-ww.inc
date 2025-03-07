SUMMARY = "Laird Connectivity Wi-Fi Summit 60 Auto World-Wide Mode"
SECTION = "Wireless"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/files/common-licenses/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

inherit update-rc.d systemd

SYSTEMD_SERVICE_${PN} = "adaptive_ww.service"
SYSTEMD_AUTO_ENABLE = "enable"

INITSCRIPT_NAME = "adaptive_ww"
INITSCRIPT_PARAMS = "defaults 30"

HFP = "${@bb.utils.contains('TUNE_FEATURES', 'callconvention-hard', 'eabihf', 'eabi', d)}"

LRD_URI ?= "${LRD_URI_BASE}"
LRD_URI_laird-internal = "https://files.devops.rfpros.com/builds/linux/adaptive_ww/laird/${PV}"

ADAP_ARCH_x86 = "-x86"
ADAP_ARCH_x86-64 = "-x86_64"
ADAP_ARCH_powerpc64 = "-powerpc64-e5500"
ADAP_ARCH_arm = "-arm-${HFP}"
ADAP_ARCH_aarch64 = "-aarch64"

SRC_URI = "${LRD_URI}/adaptive_ww${OPENSSLVER}${ADAP_ARCH}-${PV}.tar.bz2;subdir=src;name=adaptive-ww${OPENSSLVER}${ADAP_ARCH}"

do_configure[noexec] = "1"
do_compile[noexec] = "1"

S = "${WORKDIR}/src"

RDEPENDS_${PN} = "libnl libnl-genl libnl-route libcrypto libconfig"

INSANE_SKIP_${PN} = "ldflags already-stripped"
INHIBIT_PACKAGE_DEBUG_SPLIT = "1"
INHIBIT_PACKAGE_STRIP = "1"

ALLOW_EMPTY_${PN}-dev = "0"
ALLOW_EMPTY_${PN}-dbg = "0"

FILES_${PN} += "${base_libdir} ${sysconfdir}"

AWM_PARAMS = ""

do_install () {
	install -D -t ${D}${bindir} -m 755 ${S}/usr/bin/adaptive_ww
	install -D -t ${D}${base_libdir}/firmware/lrdmwl -m 644 ${S}/lib/firmware/lrdmwl/regpwr.db

	install -d ${D}${sysconfdir}/default
	echo "AWM_ARGS=${AWM_PARAMS}" > ${D}${sysconfdir}/default/adaptive_ww

	if ${@bb.utils.contains('DISTRO_FEATURES','systemd','true','false',d)}; then
		install -D -t ${D}${systemd_unitdir}/system -m 644 ${S}/usr/lib/systemd/system/adaptive_ww.service
	else
		install -D -t ${D}${sysconfdir}/init.d -m 755 ${S}/etc/init.d/adaptive_ww
	fi
}
