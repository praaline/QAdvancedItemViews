#/******************************************************************************
#** This file is part of qadvanceditemviews.
#**
#** Copyright (c) 2011-2013 Martin Hoppe martin@2x2hoppe.de
#**
#** qadvanceditemviews is free software: you can redistribute it
#** and/or modify it under the terms of the GNU Lesser General
#** Public License as published by the Free Software Foundation,
#** either version 3 of the License, or (at your option) any
#** later version.
#**
#** qadvanceditemviews is distributed in the hope that it will be
#** useful, but WITHOUT ANY WARRANTY; without even the implied
#** warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#** See the GNU General Public License for more details.
#**
#** You should have received a copy of the GNU Lesser General Public
#** License along with qadvanceditemviews.
#** If not, see <http://www.gnu.org/licenses/>.
#******************************************************************************/

TEMPLATE = lib
TARGET = qaivdesigner
include(../qaiv.pri)

CONFIG += plugin
QT += core designer widgets

INCLUDEPATH += ../qaivlib

LIBS += -L$${DESTDIR} -l$${QAIVLIB}

!isEmpty(DESIGNER_PLUGINS_DESTDIR): DESTDIR = $${DESIGNER_PLUGINS_DESTDIR}

HEADERS += \
           QAIVDesignerCollection.h \
           QAdvancedTableViewPlugin.h

SOURCES += \
           QAIVDesignerCollection.cpp \
           QAdvancedTableViewPlugin.cpp

RESOURCES += \
    QAIVDesigner.qrc

#Install the plugin in the designer plugins directory.
target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target
