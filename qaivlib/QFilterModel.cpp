/******************************************************************************
** This file is part of qadvanceditemviews.
**
** Copyright (c) 2011-2012 Martin Hoppe martin@2x2hoppe.de
**
** qadvanceditemviews is free software: you can redistribute it
** and/or modify it under the terms of the GNU Lesser General
** Public License as published by the Free Software Foundation,
** either version 3 of the License, or (at your option) any
** later version.
**
** qadvanceditemviews is distributed in the hope that it will be
** useful, but WITHOUT ANY WARRANTY; without even the implied
** warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
** See the GNU General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public
** License along with qadvanceditemviews.
** If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#include "QFilterModel.h"

#include "QAbstractFilter.h"
#include "QAutoFilter.h"
#include "QFilterGroup.h"
#include "QRangeFilter.h"
#include "QRegularExpressionFilter.h"
#include "QSelectionListFilter.h"
#include "QTextFilter.h"
#include "QValueFilter.h"

QFilterModel::QFilterModel(QObject* parent)
    : QAbstractFilterModel(parent)
{
    registerFilter(QTextFilter::Type, QIcon(":/qaiv/filter/text"), tr("Text Filter"), tr("Filter on the textual representation of values"));
    registerFilter(QRangeFilter::Type, QIcon(":/qaiv/filter/range"), tr("Range Filter"));
    registerFilter(QValueFilter::Type, QIcon(":/qaiv/filter/value"), tr("Value Filter"));
    registerFilter(QRegularExpressionFilter::Type, QIcon(":/qaiv/filter/regexp"), tr("RegExp Filter"));
    registerFilter(QAutoFilter::Type, QIcon(":/qaiv/filter/auto"), tr("Auto Filter"));
    registerFilter(QSelectionListFilter::Type, QIcon(":/qaiv/filter/selection"), tr("Selection List Filter"));
}

QFilterModel::~QFilterModel()
{
}

QAbstractFilter* QFilterModel::createFilter(const QModelIndex & index, const QVariantMap & properties) const
{
    QAbstractFilter* filter = nullptr;
    QFilterGroup* group = filterGroup(index);
    if (!group) {
        return nullptr;
    }
    if (index.row() < rowCount()) {
        if (properties.value("type").toInt() == QRangeFilter::Type) {
            filter = new QRangeFilter(index.row(), index.column());
        } else if (properties.value("type").toInt() == QValueFilter::Type) {
            filter = new QValueFilter(index.row(), index.column());
        } else if (properties.value("type").toInt() == QTextFilter::Type) {
            filter = new QTextFilter(index.row(), index.column());
        } else if (properties.value("type").toInt() == QAutoFilter::Type) {
            filter = new QAutoFilter(index.row(), index.column());
        } else if (properties.value("type").toInt() == QRegularExpressionFilter::Type) {
            filter = new QRegularExpressionFilter(index.row(), index.column());
        } else if (properties.value("type").toInt() == QSelectionListFilter::Type) {
            filter = new QSelectionListFilter(index.row(), index.column());
        }
    }
    if (filter) {
        filter->setProperty("enableOnCommit", true);
        group->add(filter);
    }
    return filter;
}
