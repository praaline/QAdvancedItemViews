/******************************************************************************
** This file is part of QAIV (QAdvanced Item Views).
**
** Copyright (c) 2011-2013 Martin Hoppe martin@2x2hoppe.de
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
#include "QAIVDesignerCollection.h"

#include "QAdvancedTableViewPlugin.h"
#include "qsearchbarplugin.h"
//#include "qtablemodelexportpushbuttonplugin.h"

QAIVDesignerCollection::QAIVDesignerCollection(QObject *parent) :
    QObject(parent)
{
    m_widgets.append(new QAdvancedTableViewPlugin());
    //    m_widgets.append(new QTableModelExportPushButtonPlugin(0));
}

QList<QDesignerCustomWidgetInterface *> QAIVDesignerCollection::customWidgets() const
{
    return m_widgets;
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qaivdesignerplugin, QAIVDesignerCollection)
#endif
