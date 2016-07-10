TEMPLATE = subdirs

SUBDIRS = core tests qml
tests.depends = core
qml.depends = core
