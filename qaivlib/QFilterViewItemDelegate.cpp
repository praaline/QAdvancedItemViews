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

#include "QFilterViewItemDelegate.h"

#include "QAbstractFilter.h"
#include "QAbstractFilterModel.h"
#include "QFilterView.h"

QFilterViewItemDelegate::QFilterViewItemDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
    m_enableFilter = false;
}

QFilterViewItemDelegate::~QFilterViewItemDelegate()
{
}

void QFilterViewItemDelegate::comboxBoxItemActivated(int index)
{
    Q_UNUSED(index);
    emit commitData((QWidget*)sender());
    emit closeEditor((QWidget*)sender());

}

void QFilterViewItemDelegate::cancelAndClose(QAbstractItemDelegate::EndEditHint hint)
{
    QWidget* w = qobject_cast<QWidget*>(sender());
    emit closeEditor(w, hint);
}

void QFilterViewItemDelegate::commitAndClose(QAbstractItemDelegate::EndEditHint hint)
{
    QWidget* w = qobject_cast<QWidget*>(sender());
    emit commitData(w);
    emit closeEditor(w, hint);
}

QWidget* QFilterViewItemDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    const QAbstractFilterModel* model = qobject_cast<const QAbstractFilterModel*>(index.model());
    if (model) {
        QAbstractFilter* filter = model->filter(index);
        if (filter) {
            return filter->createEditor(const_cast<QFilterViewItemDelegate*>(this), parent, option, index);
        } else {
            QFilterView* view = qobject_cast<QFilterView*>(parent->parentWidget());
            if (view) {
                QVariantMap properties;
                properties["column"] = index.column();
                properties["row"] = index.row();
                properties["type"] = index.data(QAbstractFilterModel::DefaultFilterTypeRole).toInt();
                filter = model->createFilter(index, properties);
                if (filter) {
                    filter->setEnabled(true);
                    return filter->createEditor(const_cast<QFilterViewItemDelegate*>(this), parent, option, index);
                }
            }
        }
    }
    return 0;
}

void QFilterViewItemDelegate::lineEditReturnPressed()
{
    emit commitData((QWidget*)sender());
    emit closeEditor((QWidget*)sender());
}

void QFilterViewItemDelegate::listWidgetCurrentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    Q_UNUSED(current)
    Q_UNUSED(previous)
    emit commitData((QWidget*)sender());
    emit closeEditor((QWidget*)sender());
}

void QFilterViewItemDelegate::setEditorData(QWidget* editor, const QModelIndex & index) const
{
    const QAbstractFilterModel* model = qobject_cast<const QAbstractFilterModel*>(index.model());
    if (model) {
        QAbstractFilter* filter = model->filter(index);
        if (filter) {
            return filter->setEditorData(editor, index);
        }
    }
}

void QFilterViewItemDelegate::setModelData(QWidget* editor, QAbstractItemModel * model, const QModelIndex & index) const
{
    const QAbstractFilterModel* m = qobject_cast<const QAbstractFilterModel*>(index.model());
    if (m) {
        QAbstractFilter* f = m->filter(index);
        if (f) {
            f->setModelData(editor, model, index);
        }
    }
}

QSize QFilterViewItemDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    return QStyledItemDelegate::sizeHint(option, index);
}

void QFilterViewItemDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    const QAbstractFilterModel* m = qobject_cast<const QAbstractFilterModel*>(index.model());
    if (m) {
        QAbstractFilter* f = m->filter(index);
        if (f) {
            f->updateEditorGeometry(editor, option, index);
        }
    }
}
