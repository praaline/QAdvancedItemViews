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
#ifndef QSELECTIONLISTFILTER_H
#define QSELECTIONLISTFILTER_H

#include "QAbstractFilter.h"
#include "QAIVLib_global.h"

//! The QSelectionListFilter class implements the filter with a fixed selection list.
/**
 * @ingroup filter
 * QSelectionListFilter provides a filter based on predefined values.
 */
class QAIVLIBSHARED_EXPORT QSelectionListFilter : public QAbstractFilter
{
public:
    enum {
        Type = 6
    };
    enum DataSource {
        Model,
        Filter
    };
    QSelectionListFilter(int row, int column);

    QWidget* createEditor(QFilterViewItemDelegate* delegate, QWidget* parent, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    /**
      * Returns the data stored under the given @p role for this filter.
      * @see setData()
      * @remarks Returns an invalid QVariant if the no data exists for the given @p role.
      */
    QVariant data(int role = Qt::DisplayRole) const;
    /**
     * Returns the data source used to populate the selection list.
     */
    QSelectionListFilter::DataSource dataSource() const;

    bool matches(const QVariant & value, int type) const;
    /**
     * Sets the database @p source for the selection list.
     */
    void setDataSource(QSelectionListFilter::DataSource source);
    /**
     * Sets the contents of the given @p editor to the data for the filter at the given @p index. Note that the @p index contains information about the filter model being used.
     */
    void setEditorData(QWidget * editor, const QModelIndex & index);
    /**
     * Sets the data for the filter at the given @p index in the filter @p model to the contents of the given @p editor.
     */
    void setModelData(QWidget* editor, QAbstractItemModel * model, const QModelIndex & index);

    void setValues(const QVariantList & values);
    /**
     * Updates the filter's @p editor geometry specified by index according to the style option given.
     */
    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem & option, const QModelIndex & index);
};

#endif // QSELECTIONLISTFILTER_H
