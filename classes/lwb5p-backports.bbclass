BACKPORTS_PROVIDER = "kernel-module-lwb5p-backports-laird"

DEPENDS += "${BACKPORTS_PROVIDER}"

NOSTDINC_FLAGS = " \
        -I${STAGING_INCDIR}/${BACKPORTS_PROVIDER}/backport-include \
        -I${STAGING_INCDIR}/${BACKPORTS_PROVIDER}/include \
        -include backport/backport.h \
        "

EXTRA_OEMAKE += "NOSTDINC_FLAGS='${NOSTDINC_FLAGS}'"
