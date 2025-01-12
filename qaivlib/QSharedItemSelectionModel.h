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
#ifndef QSHAREDITEMSELECTIONMODEL_H
#define QSHAREDITEMSELECTIONMODEL_H

#include <QItemSelectionModel>

#include "QAIVLib_global.h"

class QSharedItemSelectionModelPrivate;

//! The QSharedItemSelectionModel class implements a selection model which can be shared by other selection models.
class QAIVLIBSHARED_EXPORT QSharedItemSelectionModel : public QItemSelectionModel
{
    Q_OBJECT
public:
    /**
     * Constructs a QSharedItemSelectionModel.
     */
    QSharedItemSelectionModel(QAbstractItemModel* model, QItemSelectionModel* shared, QObject *parent = nullptr);
    /**
     * Destroys the QSharedItemSelectionModel.
     */
    ~QSharedItemSelectionModel();
public slots:
    /**
     * @reimp QItemSelectionModel::select()
     */
    void select(const QModelIndex & index, QItemSelectionModel::SelectionFlags command);
    /**
     * @reimp QItemSelectionModel::select()
     */
    void select(const QItemSelection & selection, QItemSelectionModel::SelectionFlags command);
private slots:
    void sharedSelectionChanged(const QItemSelection & selected, const QItemSelection & deselected);
private:
    QSharedItemSelectionModelPrivate* d;
};

#endif // QSHAREDITEMSELECTIONMODEL_H
