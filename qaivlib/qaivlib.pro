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

include(../qaiv.pri)

TEMPLATE = lib

TARGET = $${QAIVLIB}

QT += core widgets

CONFIG += debug_and_release

DEFINES += QAIVLIB_LIBRARY

HEADERS += \
           QAIV.h \
           QAIVLib_global.h \
           QAbstractFilter.h \
           QAbstractFilterModel.h \
           QAbstractFilterProxyModel.h \
           QAbstractModelItemDecoration.h \
           QAdvancedHeaderView.h \
           QAdvancedHeaderView_p.h \
           QAdvancedTableView.h \
           QAdvancedTableView_p.h \
           QAutoFilter.h \
           QAutoFilter_p.h \
           QCheckStateProxyModel.h \
           QClickableLabel.h \
           QConditionalDecoration.h \
           QConditionalDecorationDialog.h \
           QConditionalDecorationDialog_p.h \
           QConditionalDecorationProxyModel.h \
           QFilterEditorPopupWidget.h \
           QFilterEditorWidget.h \
           QFilterGroup.h \
           QFilterModel.h \
           QFilterModelProxy.h \
           QFilterView.h \
           QFilterViewConnector.h \
           QFilterViewItemDelegate.h \
           QFixedRowsHeaderView.h \
           QFixedRowsTableView.h \
           QGroupingProxyModel.h \
           QGroupingProxyModel_p.h \
           QHeaderViewConnector.h \
           QMimeDataUtil.h \
           QRangeFilter.h \
           QRangeFilter_p.h \
           QRegularExpressionFilter.h \
           QRegularExpressionFilter_p.h \
           QSearchBar.h \
           QSearchBar_p.h \
           QSelectionListFilter.h \
           QSelectionListFilter_p.h \
           QSharedItemSelectionModel.h \
           QSingleColumnProxyModel.h \
           QTableModelCSVWriter_p.h \
           QTableModelExcelMLWriter_p.h \
           QTableModelExportPushButton.h \
           QTableModelHTMLWriter_p.h \
           QTableModelWordMLWriter_p.h \
           QTableModelWriter.h \
           QTextFilter.h \
           QTextFilter_p.h \
           QUniqueValuesProxyModel.h \
           QValueFilter.h \
           QValueFilter_p.h

SOURCES += \
           QAIV.cpp \
           QAbstractFilter.cpp \
           QAbstractFilterModel.cpp \
           QAbstractFilterProxyModel.cpp \
           QAbstractModelItemDecoration.cpp \
           QAdvancedHeaderView.cpp \
           QAdvancedTableView.cpp \
           QAutoFilter.cpp \
           QCheckStateProxyModel.cpp \
           QClickableLabel.cpp \
           QConditionalDecoration.cpp \
           QConditionalDecorationDialog.cpp \
           QConditionalDecorationProxyModel.cpp \
           QFilterEditorPopupWidget.cpp \
           QFilterEditorWidget.cpp \
           QFilterGroup.cpp \
           QFilterModel.cpp \
           QFilterModelProxy.cpp \
           QFilterView.cpp \
           QFilterViewConnector.cpp \
           QFilterViewItemDelegate.cpp \
           QFixedRowsHeaderView.cpp \
           QFixedRowsTableView.cpp \
           QGroupingProxyModel.cpp \
           QHeaderViewConnector.cpp \
           QMimeDataUtil.cpp \
           QRangeFilter.cpp \
           QRegularExpressionFilter.cpp \
           QSearchBar.cpp \
           QSelectionListFilter.cpp \
           QSharedItemSelectionModel.cpp \
           QSingleColumnProxyModel.cpp \
           QTableModelCSVWriter.cpp \
           QTableModelExcelMLWriter.cpp \
           QTableModelExportPushButton.cpp \
           QTableModelHTMLWriter.cpp \
           QTableModelWordMLWriter.cpp \
           QTableModelWriter.cpp \
           QTextFilter.cpp \
           QUniqueValuesProxyModel.cpp \
           QValueFilter.cpp

FORMS += \
         QAdvancedTableView.ui \
         QConditionalDecorationDialog.ui \
         QSearchBar.ui

TRANSLATIONS += QAIVLib_de.ts \
        QAIVLib_ru.ts

RESOURCES += \
    QAIV.qrc
