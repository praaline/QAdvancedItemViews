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

#include "QFilterViewConnector.h"
#include "QFilterView.h"

#include <QHeaderView>
#include <QScrollBar>
#include <QTableView>
#include <QTreeView>

QFilterViewConnector::QFilterViewConnector(QFilterView* filterView) :
    QObject(filterView)
{
    cFilterView = filterView;
    cTableView = 0;
    cTreeView = 0;

    connect(cFilterView->horizontalHeader(), &QHeaderView::sectionMoved, this, &QFilterViewConnector::filterViewHorizontalSectionMoved);
    connect(cFilterView->horizontalHeader(), &QHeaderView::sectionResized, this, &QFilterViewConnector::filterViewHorizontalSectionResized);
    connect(cFilterView->horizontalHeader(), &QHeaderView::sortIndicatorChanged, this, &QFilterViewConnector::filterViewHorizontalSortIndicatorChanged);
}

QFilterViewConnector::QFilterViewConnector(QFilterView* filterView, QTableView* tableView, QObject* parent) :
    QObject(parent)
{
    cFilterView = filterView;
    cTableView = tableView;
    cTreeView = 0;

    connect(cFilterView->horizontalHeader(), &QHeaderView::sectionMoved, this, &QFilterViewConnector::filterViewHorizontalSectionMoved);
    connect(cFilterView->horizontalHeader(), &QHeaderView::sectionResized, this, &QFilterViewConnector::filterViewHorizontalSectionResized);
    connect(cFilterView->horizontalHeader(), &QHeaderView::sortIndicatorChanged, this, &QFilterViewConnector::filterViewHorizontalSortIndicatorChanged);

    setDataView(tableView);
}

QFilterViewConnector::QFilterViewConnector(QFilterView* filterView, QTreeView* treeView, QObject* parent) :
    QObject(parent)
{
    cFilterView = filterView;
    cTableView = 0;
    cTreeView = treeView;

    connect(cFilterView->horizontalHeader(), &QHeaderView::sectionMoved, this, &QFilterViewConnector::filterViewHorizontalSectionMoved);
    connect(cFilterView->horizontalHeader(), &QHeaderView::sectionResized, this, &QFilterViewConnector::filterViewHorizontalSectionResized);
    connect(cFilterView->horizontalHeader(), &QHeaderView::sortIndicatorChanged, this, &QFilterViewConnector::filterViewHorizontalSortIndicatorChanged);

    setDataView(treeView);
}

void QFilterViewConnector::setDataView(QTableView *view)
{
    if (cTableView) {
        disconnect(cFilterView->horizontalHeader(), 0, this, 0);
        disconnect(cTableView->horizontalScrollBar(), 0, this, 0);
        disconnect(cTableView->verticalHeader(), 0, this, 0);
    }
    cTableView = view;
    if (cTableView) {
        connect(cTableView->horizontalHeader(), &QHeaderView::sectionMoved, this, &QFilterViewConnector::dataViewHorizontalSectionMoved);
        connect(cTableView->horizontalHeader(), &QHeaderView::sectionResized, this, &QFilterViewConnector::dataViewHorizontalSectionResized);
        connect(cTableView->horizontalHeader(), &QHeaderView::sortIndicatorChanged, this, &QFilterViewConnector::dataViewHorizontalSortIndicatorChanged);
        connect(cTableView->horizontalScrollBar(), &QAbstractSlider::rangeChanged, this, &QFilterViewConnector::dataViewHorizontalScrollBarRangeChanged);
        connect(cTableView->horizontalScrollBar(), &QAbstractSlider::sliderMoved, this, &QFilterViewConnector::dataViewHorizontalScrollBarSilderMoved);

        connect(cTableView->verticalHeader(), &QHeaderView::sectionCountChanged, this, &QFilterViewConnector::adjustVerticalHeaderWidth);
        connect(cTableView->verticalScrollBar(), &QAbstractSlider::rangeChanged, this, &QFilterViewConnector::dataViewVerticalScrollBarRangeChanged);
    }
}

void QFilterViewConnector::setDataView(QTreeView *view)
{
    if (cTreeView) {
        disconnect(cTreeView->header(), 0, this, 0);
        disconnect(cTreeView->horizontalScrollBar(), 0, this, 0);
    }
    cTreeView = view;
    if (cTreeView) {
        connect(cTreeView->header(), &QHeaderView::sectionMoved, this, &QFilterViewConnector::dataViewHorizontalSectionMoved);
        connect(cTreeView->header(), &QHeaderView::sectionResized, this, &QFilterViewConnector::dataViewHorizontalSectionResized);
        connect(cTreeView->header(), &QHeaderView::sortIndicatorChanged, this, &QFilterViewConnector::dataViewHorizontalSortIndicatorChanged);
        connect(cTreeView->horizontalScrollBar(), &QAbstractSlider::rangeChanged, this, &QFilterViewConnector::dataViewHorizontalScrollBarRangeChanged);
        connect(cTreeView->horizontalScrollBar(), &QAbstractSlider::sliderMoved, this, &QFilterViewConnector::dataViewHorizontalScrollBarSilderMoved);
    }
}

void QFilterViewConnector::adjustVerticalHeaderWidth()
{
    if (cTableView) {
        if (cTableView->verticalHeader()->width() < cFilterView->verticalHeader()->width()) {
            cTableView->verticalHeader()->blockSignals(true);
            cTableView->verticalHeader()->setFixedWidth(cFilterView->verticalHeader()->width());
            cTableView->verticalHeader()->blockSignals(false);
        } else {
            cFilterView->verticalHeader()->blockSignals(true);
            cFilterView->verticalHeader()->setFixedWidth(cTableView->verticalHeader()->width());
            cFilterView->verticalHeader()->blockSignals(false);

        }
        if (cFilterView->model()->rowCount() > cFilterView->maxVisibileFilterSets()) {
            cTableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        }
    }
}

void QFilterViewConnector::dataViewHorizontalScrollBarRangeChanged(int min, int max)
{
    cFilterView->horizontalScrollBar()->setRange(min, max);
}

void QFilterViewConnector::dataViewHorizontalScrollBarSilderMoved(int value)
{
    cFilterView->horizontalScrollBar()->setValue(value);
}

void QFilterViewConnector::dataViewHorizontalSortIndicatorChanged(int logicalIndex, Qt::SortOrder order)
{
    cFilterView->horizontalHeader()->blockSignals(true);
    cFilterView->sortByColumn(logicalIndex, order);
    cFilterView->horizontalHeader()->blockSignals(false);
}

void QFilterViewConnector::dataViewHorizontalSectionMoved(int logicalIndex, int oldVisualIndex, int newVisualIndex)
{
    Q_UNUSED(logicalIndex);
    cFilterView->horizontalHeader()->moveSection(oldVisualIndex, newVisualIndex);
}

void QFilterViewConnector::dataViewHorizontalSectionResized(int logicalIndex, int oldSize, int newSize)
{
    Q_UNUSED(oldSize);
    cFilterView->horizontalHeader()->resizeSection(logicalIndex, newSize);
}

void QFilterViewConnector::dataViewVerticalScrollBarRangeChanged(int min, int max)
{
    Q_UNUSED(min);
    Q_UNUSED(max);
    if (cTableView) {
        if (cTableView->verticalScrollBar()->maximum() == 0) {
            cFilterView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        } else {
            cFilterView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        }
    } else if (cTreeView) {
        if (cTreeView->verticalScrollBar()->maximum() == 0){
            cFilterView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        } else {
            cFilterView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        }
    }

}

void QFilterViewConnector::filterViewHorizontalSectionMoved(int logicalIndex, int oldVisualIndex, int newVisualIndex)
{
    Q_UNUSED(logicalIndex);
    if (cTableView) {
        cTableView->horizontalHeader()->moveSection(oldVisualIndex, newVisualIndex);
    } else if (cTreeView) {
        cTreeView->header()->moveSection(oldVisualIndex, newVisualIndex);
    }
}

void QFilterViewConnector::filterViewHorizontalSectionResized(int logicalIndex, int oldSize, int newSize)
{
    Q_UNUSED(oldSize);
    if (cTableView) {
        cTableView->horizontalHeader()->resizeSection(logicalIndex, newSize);
    } else if (cTreeView) {
        cTreeView->header()->resizeSection(logicalIndex, newSize);
    }
}

void QFilterViewConnector::filterViewHorizontalSortIndicatorChanged(int logicalIndex, Qt::SortOrder order)
{
    if (cTableView) {
        cTableView->sortByColumn(logicalIndex, order);
    } else if (cTreeView) {
        cTreeView->sortByColumn(logicalIndex, order);
    }
}
