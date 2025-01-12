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
#ifndef QFILTERVIEW_H
#define QFILTERVIEW_H

#include <QTableView>

#include "QAIVLib_global.h"
#include "QFilterViewConnector.h"

class QAbstractItemView;
class QFilterViewConnector;
class QFilterViewPrivate;

//! The QFilterView class provides a widget that is used to view and edit filter definitions.
/**
  * @ingroup views
  * @image html qfilterview01.png
  */
class QAIVLIBSHARED_EXPORT QFilterView : public QTableView
{
    Q_OBJECT
    //! @property(maxVisibileFilterSets)
    /**
      * @see maxVisibileFilterSets() setMaxVisibileFilterSets()
      */
    Q_PROPERTY(int maxVisibileFilterSets READ maxVisibileFilterSets WRITE setMaxVisibileFilterSets)

public:
    QFilterView(QWidget* parent = nullptr);
    ~QFilterView();

    void connectToView(QAbstractItemView* view);

    int defaultFilterType() const;

    QFilterViewConnector* filterViewConnector() const;

    bool filterVisible() const;

    int maxVisibileFilterSets() const;

    void setAllowedFilterTypes(int types);

    void setDefaultFilterType(int type);

    void setMaxVisibileFilterSets(int rows);

    void setModel(QAbstractItemModel* model) override;

    void toggleFilter(const QModelIndex & index);

signals:
    void calcGeometryRequested();
    void cornerButtonClicked();
    void focusReceived();
    /**
      * This signal is emitted if the visility of the filter sets has been changed.
      */
    void visibilityChanged(bool visible);
    void removeColumnFilter(int row, int column);

public slots:
    void addFilter();
    /**
      * Opens the color selection dialog for the current index.
      */
    void changeColor();
    void changeProperties();
    void disableSelectedFilters();
    void enableSelectedFilters();
    /**
     * Removes the current filter.
     */
    void removeFilter();
    /**
      * If @p visible the filters in the filter model are shown. Otherwise the size of this is reduced to show the header view only.
      */
    void setFilterVisible(bool visible);
    /**
     * Toggles the state (enabled/disabled) of the filter selection.
     * @see toggleFilter()
     */
    void toggleSelectedFilters();

protected:
    void contextMenuEvent(QContextMenuEvent* event) override;
    void focusInEvent(QFocusEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private slots:
    void hideFilter();
    void showFilter();

private:
    void updateGeometry();

    QFilterViewPrivate* d;
};

#endif // QFILTERVIEW_H
