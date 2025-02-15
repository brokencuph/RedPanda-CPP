TEMPLATE = subdirs

SUBDIRS += \
    RedPandaIDE \
    astyle \
    consolepauser

# Add the dependencies so that the RedPandaIDE project can add the depended programs
# into the main app bundle
RedPandaIDE.depends = astyle consolepauser

win32: {
SUBDIRS += \
    redpanda-win-git-askpass
    RedPandaIDE.depends += redpanda-win-git-askpass
}

unix: {
SUBDIRS += \
    redpanda-git-askpass
    RedPandaIDE.depends += redpanda-git-askpass
}

APP_NAME = RedPandaCPP

APP_VERSION = 1.1.0

linux: {
    isEmpty(PREFIX) {
        PREFIX = /usr/local
    }

    QMAKE_SUBSTITUTES += linux/redpandaide.desktop.in

    resources.path = $${PREFIX}/share/$${APP_NAME}
    resources.files += linux/templates
    INSTALLS += resources

    docs.path = $${PREFIX}/share/doc/$${APP_NAME}
    docs.files += README.md
    docs.files += NEWS.md
    docs.files += LICENSE
    INSTALLS += docs

    pixmaps.path = $${PREFIX}/share/pixmaps
    pixmaps.files += linux/redpandaide.png
    INSTALLS += pixmaps

    desktop.path = $${PREFIX}/share/applications
    desktop.files += linux/redpandaide.desktop
    INSTALLS += desktop
}

win32: {
    !isEmpty(PREFIX) {
        target.path = $${PREFIX}
        QMAKE_SUBSTITUTES += windows/installer-scripts/config.nsh.in
        QMAKE_SUBSTITUTES += windows/installer-scripts/config32.nsh.in
        QMAKE_SUBSTITUTES += windows/installer-scripts/config-clang.nsh.in

        resources.path = $${PREFIX}
        resources.files += windows/templates
        resources.files += windows/installer-scripts/config.nsh
        resources.files += windows/installer-scripts/config32.nsh
        resources.files += windows/installer-scripts/config-clang.nsh
        resources.files += README.md
        resources.files += NEWS.md
        resources.files += LICENSE
        resources.files += RedPandaIDE/images/devcpp.ico

        INSTALLS += resources
    }
}
