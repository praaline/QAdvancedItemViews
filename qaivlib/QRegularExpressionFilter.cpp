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

#include "QRegularExpressionFilter.h"

#include <QRegularExpressionFilter_p.h>

#include <QCheckBox>
#include <QComboBox>
#include <QDebug>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QRegularExpression>

#include "QClickableLabel.h"

QRegExpFilterEditor::QRegExpFilterEditor(QWidget* parent)
    : QWidget(parent)
{
    QHBoxLayout* l = new QHBoxLayout(this);
    l->setSpacing(0);
    l->setContentsMargins(0, 0, 0, 0);
    l->setSpacing(6);

    m_patternEdit = new QLineEdit(this);
    l->addWidget(m_patternEdit);

    m_sensitivityLabel = new QClickableLabel(this);
    connect(m_sensitivityLabel, &QClickableLabel::clicked, this, &QRegExpFilterEditor::sensitivityLabelClicked);
    l->addWidget(m_sensitivityLabel);

    setFocusProxy(m_patternEdit);

    setCaseSensitivity(Qt::CaseInsensitive);
    setFocusPolicy(Qt::StrongFocus);
    setAutoFillBackground(true);
}

QRegExpFilterEditor::~QRegExpFilterEditor()
{
}

Qt::CaseSensitivity QRegExpFilterEditor::caseSenstivity() const
{
    return m_sensitivity;
}

void QRegExpFilterEditor::sensitivityLabelClicked(Qt::MouseButtons buttons)
{
    if (buttons.testFlag(Qt::LeftButton)) {
        if (m_sensitivity == Qt::CaseInsensitive) {
            setCaseSensitivity(Qt::CaseSensitive);
        } else {
            setCaseSensitivity(Qt::CaseInsensitive);
        }
    }
}

QString QRegExpFilterEditor::pattern() const
{
    return m_patternEdit->text();
}

void QRegExpFilterEditor::setCaseSensitivity(Qt::CaseSensitivity sensitivity)
{
    if (sensitivity == Qt::CaseSensitive) {
        m_sensitivityLabel->setPixmap(QPixmap(QString::fromUtf8(":/qaiv/filter/case_sensitive")));
        m_sensitivityLabel->setToolTip(tr("The filter is case sensitive"));
    } else {
        m_sensitivityLabel->setPixmap(QPixmap(QString::fromUtf8(":/qaiv/filter/case_insensitive")));
        m_sensitivityLabel->setToolTip(tr("The filter is case insensitive"));
    }
    m_sensitivity = sensitivity;
}

void QRegExpFilterEditor::setPattern(const QString &pattern)
{
    m_patternEdit->setText(pattern);
}

QRegularExpressionFilter::QRegularExpressionFilter(int row, int column) :
    QAbstractFilter(QRegularExpressionFilter::Type, row, column)
{
    setProperty("caseSensitivity", Qt::CaseInsensitive);
}

QWidget* QRegularExpressionFilter::createEditor(QFilterViewItemDelegate* delegate, QWidget* parent, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    Q_UNUSED(delegate)
    Q_UNUSED(option)
    Q_UNUSED(index)
    return new QRegExpFilterEditor(parent);
}

QVariant QRegularExpressionFilter::data(int role) const
{
    if (role == Qt::DisplayRole) {
        return QString("%1").arg(property("pattern").toString());
    }
    return QVariant();
}

bool QRegularExpressionFilter::matches(const QVariant & value, int type) const
{
    Q_UNUSED(type);
    QRegularExpression::PatternOptions options;
    if (static_cast<Qt::CaseSensitivity>(property("caseSensitivity").toInt()) == Qt::CaseInsensitive)
        options =  QRegularExpression::CaseInsensitiveOption;
    QRegularExpression regExp(property("pattern").toString(), options);
    QRegularExpressionMatch match = regExp.match(value.toString());
    if (match.hasMatch())
        return true;
    return false;
}

void QRegularExpressionFilter::setEditorData(QWidget * editor, const QModelIndex & index)
{
    Q_UNUSED(index)
    QRegExpFilterEditor* w = qobject_cast<QRegExpFilterEditor*>(editor);
    if (w) {
        w->setCaseSensitivity(static_cast<Qt::CaseSensitivity>(property("caseSensitivity").toInt()));
        w->setPattern(property("pattern").toString());
    }
}

void QRegularExpressionFilter::setModelData(QWidget* editor, QAbstractItemModel * model, const QModelIndex & index)
{
    QRegExpFilterEditor* w = qobject_cast<QRegExpFilterEditor*>(editor);
    if (w) {
        QVariantMap p(index.data(Qt::EditRole).toMap());
        p["pattern"] = w->pattern();
        p["caseSensitivity"] = w->caseSenstivity();
        if (property("enableOnCommit").toBool()) {
            p["enabled"] = true;
        }
        model->setData(index, p);
    }
}

void QRegularExpressionFilter::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem & option, const QModelIndex & index)
{
    Q_UNUSED(index)
    editor->setGeometry(option.rect);
}

QDebug operator<<(QDebug d, const QRegularExpressionFilter & f)
{
    d << "(QRegExpFilter:"
      << "row:" << f.row()
      << "column:" << f.column()
      << "enabled:" << f.isEnabled()
      << "caseSensitivity:" << static_cast<Qt::CaseSensitivity>(f.property("caseSensitivity").toInt())
      << "pattern:" << f.property("pattern").toString()
      << ")";
    return d.space();
}
