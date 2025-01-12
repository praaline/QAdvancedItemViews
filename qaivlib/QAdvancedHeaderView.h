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
#ifndef QADVANCEDHEADERVIEW_H
#define QADVANCEDHEADERVIEW_H

#include <QHeaderView>

#include "QAIVLib_global.h"

//! The QAdvancedHeaderView class provides a header view to manage to appearance of the related view.
/**
 * @image html qadvancedheaderview01.png QAdvancedHeaderView
 * <h2>Features</h2>
 * <h3>Context Menus</h3>
 * The header view provides context menus to manage the view settings and to create, edit and delete filter.
 * @image html qadvancedheaderview02.png QAdvancedHeaderView Context Menu - Column Header
 * @image html qadvancedheaderview03.png QAdvancedHeaderView Context Menu - Filter Model
 *
 */
class QAIVLIBSHARED_EXPORT QAdvancedHeaderView : public QHeaderView
{
    Q_OBJECT
public:
    /**
      * Creates a new generic header with the given @p orientation and @p parent.
      */
    QAdvancedHeaderView(Qt::Orientation orientation, QWidget* parent = nullptr);
    /**
      * Destroys the header.
      */
    ~QAdvancedHeaderView();

public slots:
    /**
      * Shows all columns.
      */
    void showAllColumns();

private slots:
    void addFilterSetActionTriggered();

    void hideFilterActionTriggered();

    void filterModeActionTriggered();

    void hideSectionActionTriggered();

    void highlightModeActionTriggered();

    void invertedMatchModeActionTriggered();

    void moreColumnsActionTriggered();

    void removeFilterSetActionTriggered();

    void renameFilterActionTriggered();

    void sectionToggled(bool on);

    void showFilterActionTriggered();

    void toggleSortOrderActionTriggered();

protected:
    void contextMenuEvent(QContextMenuEvent * event);
};

#endif // QADVANCEDHEADERVIEW_H
