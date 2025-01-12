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

#include "QAutoFilter.h"

#include "QAbstractFilterModel.h"
#include "QAutoFilter_p.h"
#include "QCheckStateProxyModel.h"
#include "QFilterViewItemDelegate.h"
#include "QUniqueValuesProxyModel.h"
#include "QSingleColumnProxyModel.h"

#include <QtWidgets>
#include <QProgressDialog>

QAutoFilterEditorPopup::QAutoFilterEditorPopup(QWidget* parent) :
    QFilterEditorPopupWidget(parent)
{
    m_progress = new QProgressDialog(this);
    m_progress->setMaximum(100);
    m_mode = 0; // 0 = Selected values 1 = empty 2 = not empty
    QVBoxLayout* l = new QVBoxLayout();
    l->setContentsMargins(6, 6, 6, 6);

    QVBoxLayout* lb = new QVBoxLayout();
    lb->setSpacing(3);
    m_emptyToolButton = new QToolButton(this);
    m_emptyToolButton->setText(tr("Empty"));
    m_emptyToolButton->setAutoRaise(true);
    m_emptyToolButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    lb->addWidget(m_emptyToolButton);
    connect(m_emptyToolButton, &QAbstractButton::clicked, this, &QAutoFilterEditorPopup::emptyToolButtonClicked);

    m_notEmptyToolButton = new QToolButton(this);
    m_notEmptyToolButton->setText(tr("Not Empty"));
    m_notEmptyToolButton->setAutoRaise(true);
    m_notEmptyToolButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    lb->addWidget(m_notEmptyToolButton);
    l->addLayout(lb);
    connect(m_notEmptyToolButton, &QAbstractButton::clicked, this, &QAutoFilterEditorPopup::notEmptyToolButtonClicked);

    QFrame* f = new QFrame(this);
    f->setFrameShape(QFrame::HLine);
    f->setFrameShadow(QFrame::Sunken);
    l->addWidget(f);

    m_lineEdit = new QLineEdit(this);
    m_lineEdit->setMinimumWidth(200);
    m_lineEdit->setPlaceholderText(tr("Search for"));
    connect(m_lineEdit, &QLineEdit::textEdited, this, &QAutoFilterEditorPopup::searchForTextEdited);

    l->addWidget(m_lineEdit);
    m_listView = new QListView(this);
    l->addWidget(m_listView);
    setLayout(l);

    m_checkStateProxy = new QCheckStateProxyModel(this);
    connect(m_checkStateProxy, &QAbstractItemModel::dataChanged, this, &QAutoFilterEditorPopup::checkStateProxyDataChanged);

    m_singleColumnProxy = new QSingleColumnProxyModel(this);
    m_singleValueProxy = new QUniqueValuesProxyModel(this);
    connect(m_singleValueProxy, &QUniqueValuesProxyModel::progressChanged, this, &QAutoFilterEditorPopup::uniqueValueModelProgressChanged);
    m_singleValueProxy->setEmptyItemsAllowed(false);

    m_singleColumnProxy->setSourceModel(m_singleValueProxy);
    m_checkStateProxy->setSourceModel(m_singleColumnProxy);
    m_listView->setModel(m_checkStateProxy);

    m_selectCheckBox = new QCheckBox(this);
    m_selectCheckBox->setText(tr("Select/Deselect all"));
    m_selectCheckBox->setTristate(true);
    m_selectCheckBox->installEventFilter(parent);
    connect(m_selectCheckBox, &QCheckBox::stateChanged, this, &QAutoFilterEditorPopup::selectCheckBoxStateChanged);

    l->addWidget(m_selectCheckBox);
    m_listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_listView->installEventFilter(parent);

    QDialogButtonBox* b = new QDialogButtonBox(this);
    b->addButton(QDialogButtonBox::Ok);
    b->addButton(QDialogButtonBox::Cancel);
    connect(b, &QDialogButtonBox::accepted, this, &QAutoFilterEditorPopup::accepted);
    connect(b, &QDialogButtonBox::rejected, this, &QAutoFilterEditorPopup::rejected);
    l->addWidget(b);
}

QAutoFilterEditorPopup::~QAutoFilterEditorPopup()
{
}

void QAutoFilterEditorPopup::checkStateProxyDataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight)
{
    Q_UNUSED(topLeft);
    Q_UNUSED(bottomRight);
    m_selectCheckBox->blockSignals(true);
    if (m_checkStateProxy->checkedIndexes().size() == 0) {
        m_selectCheckBox->setCheckState(Qt::Unchecked);
    } else if(m_checkStateProxy->checkedIndexes().size() == (m_checkStateProxy->checkableColumnsCount() * m_checkStateProxy->rowCount())) {
        m_selectCheckBox->setCheckState(Qt::Checked);
    } else {
        m_selectCheckBox->setCheckState(Qt::PartiallyChecked);
    }
    m_selectCheckBox->blockSignals(false);
}

void QAutoFilterEditorPopup::emptyToolButtonClicked()
{
    m_mode = 1;
    emit modeChanged();
}

int QAutoFilterEditorPopup::mode() const
{
    return m_mode;
}

void QAutoFilterEditorPopup::notEmptyToolButtonClicked()
{
    m_mode = 2;
    emit modeChanged();
}

void QAutoFilterEditorPopup::searchForTextEdited(const QString & text)
{
    QModelIndexList mIndexes = m_checkStateProxy->match(m_checkStateProxy->index(0,0), Qt::DisplayRole, text);
    if (!mIndexes.isEmpty()) {
        m_listView->setCurrentIndex(mIndexes.first());
    }
}

void QAutoFilterEditorPopup::selectCheckBoxStateChanged(int state)
{
    if (state == Qt::Checked) {
        m_checkStateProxy->setAllChecked(true);
    } else if (state == Qt::Unchecked) {
        m_checkStateProxy->setAllChecked(false);
    } else if (state == Qt::PartiallyChecked) {
        m_selectCheckBox->setChecked(true);
    }
}

QVariantList QAutoFilterEditorPopup::selectedValues(int role) const
{
    QVariantList v;
    Q_FOREACH(QModelIndex mIndex, m_checkStateProxy->checkedIndexes()) {
        v.append(mIndex.data(role));
    }
    return v;
}

void QAutoFilterEditorPopup::setSelectedValues(const QVariantList & values)
{
    m_checkStateProxy->setCheckedValues(0, values);
}

void QAutoFilterEditorPopup::setSourceModel(QAbstractItemModel *model, int column)
{
    m_singleValueProxy->setModelColumn(column);
    m_singleValueProxy->setSourceModel(model);
    m_singleColumnProxy->setSourceModelColumn(column);
    m_singleColumnProxy->sort(0);
    m_checkStateProxy->setColumnCheckable(0);
}

void QAutoFilterEditorPopup::uniqueValueModelProgressChanged(int progress)
{
    m_progress->setValue(progress);
}

QAutoFilterEditor::QAutoFilterEditor(QWidget *parent) :
    QFilterEditorWidget(parent)
{
    QAutoFilterEditorPopup *popup = new QAutoFilterEditorPopup(this);
    setPopup(popup);
    setFocusProxy(popup);
    connect(popup, &QAutoFilterEditorPopup::modeChanged, this, &QAutoFilterEditor::modeSelected);
    connect(popup, &QAutoFilterEditorPopup::accepted, this, [=] { emit commitAndClose(); });
    connect(popup, &QAutoFilterEditorPopup::rejected, this, [=] { emit cancelAndClose(); });
    setFocusPolicy(Qt::StrongFocus);
}

void QAutoFilterEditor::modeSelected()
{
    emit commitAndClose();
}

void QAutoFilterEditor::setSourceModel(QAbstractItemModel *model, int column)
{
    QAutoFilterEditorPopup* e = qobject_cast<QAutoFilterEditorPopup*>(popup());
    e->setSourceModel(model, column);
}

QAutoFilter::QAutoFilter(int row, int column) :
    QAbstractFilter(QAutoFilter::Type, row, column)
{
}

QWidget* QAutoFilter::createEditor(QFilterViewItemDelegate* delegate, QWidget* parent, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QAutoFilterEditor* e = new QAutoFilterEditor(parent);
    QObject::connect(e, &QFilterEditorWidget::cancelAndClose, delegate, &QFilterViewItemDelegate::cancelAndClose);
    QObject::connect(e, &QFilterEditorWidget::commitAndClose, delegate, &QFilterViewItemDelegate::commitAndClose);
    return e;
}

QVariant QAutoFilter::data(int role) const
{
    if (role == Qt::DisplayRole) {
        if (property("mode").toInt() == 0) {
            if (property("selectedValues").toList().isEmpty()){
                return QObject::tr("<none>");
            } else {
                if (property("selectedValues").toList().size() == 1) {
                    return QString(QObject::tr("%1 entry")).arg(property("selectedValues").toList().size());
                } else {
                    return QString(QObject::tr("%1 entries")).arg(property("selectedValues").toList().size());
                }
            }
        } else if (property("mode").toInt() == 1) {
            return QObject::tr("Empty");
        } else if (property("mode").toInt() == 2) {
            return QObject::tr("Not Empty");
        }
    }
    return QVariant();
}

bool QAutoFilter::matches(const QVariant & value, int type) const
{
    Q_UNUSED(type);
    if (property("mode").toInt() == 1) {
        return value.toString().isEmpty();
    } else if (property("mode").toInt() == 2) {
        return !value.toString().isEmpty();
    }
    return property("selectedValues").toList().contains(value);
}

void QAutoFilter::setEditorData(QWidget* editor, const QModelIndex & index)
{
    QAutoFilterEditor* w = qobject_cast<QAutoFilterEditor*>(editor);
    if (w) {
        QAutoFilterEditorPopup* p = qobject_cast<QAutoFilterEditorPopup*>(w->popup());
        QAbstractFilterModel* m = qobject_cast<QAbstractFilterModel*>((QAbstractItemModel*)index.model());
        if (m) {
            p->setSourceModel(m->sourceModel(), column());
            p->setSelectedValues(property("selectedValues").toList());
        }
    }
}

void QAutoFilter::setModelData(QWidget* editor, QAbstractItemModel * model, const QModelIndex & index)
{
    QAutoFilterEditor* w = qobject_cast<QAutoFilterEditor*>(editor);
    if (w) {
        QAutoFilterEditorPopup* p = qobject_cast<QAutoFilterEditorPopup*>(w->popup());
        QVariantMap properties(index.data(Qt::EditRole).toMap());
        properties["selectedValues"] = p->selectedValues();
        properties["mode"] = p->mode();
        if (p->mode() > 0) {
            properties["selectedValues"] = QVariantList();
        } else {
            properties["selectedValues"] = p->selectedValues();
        }
        if (property("enableOnCommit").toBool()) {
            properties["enabled"] = true;
        }
        model->setData(index, properties);
    }
}

void QAutoFilter::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem & option, const QModelIndex & index)
{
    Q_UNUSED(index);
    QAutoFilterEditor* e = qobject_cast<QAutoFilterEditor*>(editor);
    if (e) {
        e->setGeometry(option.rect);
        e->showPopup();
    }
}
