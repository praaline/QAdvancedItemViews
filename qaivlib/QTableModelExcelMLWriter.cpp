/******************************************************************************
** This file is part of qadvanceditemviews.
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

#include "QTableModelExcelMLWriter_p.h"

#include "QAIV.h"
#include "QAdvancedTableView.h"
#include "QAbstractFilterProxyModel.h"
#include "QMimeDataUtil.h"

#include <QDebug>
#include <QIODevice>
#include <QTableView>
#include <QXmlStreamWriter>

QTableModelExcelMLWriter::QTableModelExcelMLWriter(QIODevice* device)
    : m_device(device), m_includeHeader(true), m_role(Qt::DisplayRole)
{
}

QTableModelExcelMLWriter::~QTableModelExcelMLWriter()
{
}

void QTableModelExcelMLWriter::setIncludeHeader(bool on)
{
    m_includeHeader = on;
}

void QTableModelExcelMLWriter::setRole(int role)
{
    m_role = role;
}

bool QTableModelExcelMLWriter::write(QAdvancedTableView* view, bool all)
{
    if (!m_device->isWritable() && ! m_device->open(QIODevice::WriteOnly)) {
        qWarning() << "QTableModelExcelMLWriter::writeAll: the device can not be opened for writing";
        return false;
    }
    QXmlStreamWriter stream(m_device);
    stream.setAutoFormatting(true);
    stream.setAutoFormattingIndent(2);

    stream.writeStartDocument("1.0");
    stream.writeProcessingInstruction("mso-application progid=\"Excel.Sheet\"");

    stream.writeStartElement("Workbook");
    stream.writeAttribute("xmlns", "urn:schemas-microsoft-com:office:spreadsheet");
    stream.writeAttribute("xmlns:o", "urn:schemas-microsoft-com:office:office");
    stream.writeAttribute("xmlns:x", "urn:schemas-microsoft-com:office:excel");
    stream.writeAttribute("xmlns:ss", "urn:schemas-microsoft-com:office:spreadsheet");
    stream.writeAttribute("xmlns:html", "http://www.w3.org/TR/REC-html40");

    stream.writeStartElement("Styles");
    stream.writeStartElement("Style");
    stream.writeAttribute("ss:ID", "Default");
    stream.writeAttribute("ss:Name", "Normal");
    stream.writeStartElement("Alignment");
    stream.writeAttribute("ss:Vertical", "Bottom");
    stream.writeEndElement();
    stream.writeEmptyElement("Borders");
    stream.writeEmptyElement("Font");
    stream.writeAttribute("ss:FontName", "Calibri");
    stream.writeAttribute("x:Family", "Swiss");
    stream.writeAttribute("ss:Size", "11");
    stream.writeAttribute("ss:Color", "#000000");
    stream.writeEmptyElement("Interior");
    stream.writeEmptyElement("NumberFormat");
    stream.writeEmptyElement("Protection");
    // </Style>

    stream.writeEndElement();
    // tag <Styles)
    stream.writeEndElement();

    stream.writeStartElement("Worksheet");
    stream.writeAttribute("ss:Name", QObject::tr("Sheet1"));

    stream.writeStartElement("Table");
    QPair<QModelIndex, QModelIndex> e;
    if (!all) {
        e = selectionEdges(view->selectionModel()->selection());
    } else {
        e.first = view->filterProxyModel()->index(0, 0);
        e.second = view->filterProxyModel()->index(view->filterProxyModel()->rowCount() - 1, view->filterProxyModel()->columnCount() - 1);
    }
    if (m_includeHeader) {
        stream.writeStartElement("Row");
        for (int c = e.first.column(); c <= e.second.column(); c++) {
            if (!view->horizontalHeader()->isSectionHidden(c)) {
                stream.writeStartElement("Cell");

                stream.writeStartElement("Data");
                stream.writeAttribute("ss:Type", "String");
                stream.writeCharacters(view->filterProxyModel()->headerData(view->horizontalHeader()->visualIndex(c), Qt::Horizontal, m_role).toString());
                // end tag <Data>
                stream.writeEndElement();
                // end tag <Cell>
                stream.writeEndElement();
            }
        }
        // end tag <Row>
        stream.writeEndElement();
    }
    for (int r = e.first.row(); r <= e.second.row(); r++) {
        stream.writeStartElement("Row");
        for (int c = e.first.column(); c <= e.second.column(); c++) {
            if (!view->horizontalHeader()->isSectionHidden(c)) {
                stream.writeStartElement("Cell");

                stream.writeStartElement("Data");
                stream.writeAttribute("ss:Type", "String");
                stream.writeCharacters(view->filterProxyModel()->index(r, view->horizontalHeader()->visualIndex(c)).data(m_role).toString());
                // end tag <Data>
                stream.writeEndElement();
                // end tag <Cell>
                stream.writeEndElement();
            }
        }
        // end tag <Row>
        stream.writeEndElement();
    }
    // end tag <Table>
    stream.writeEndElement();
    stream.writeEndElement();
    //
    stream.writeEndElement();
    return true;
}

bool QTableModelExcelMLWriter::write(QTableView* view, bool all)
{
    if (!m_device->isWritable() && ! m_device->open(QIODevice::WriteOnly)) {
        qWarning() << "QTableModelExcelMLWriter::writeAll: the device can not be opened for writing";
        return false;
    }
    QXmlStreamWriter stream(m_device);
    stream.setAutoFormatting(true);
    stream.setAutoFormattingIndent(2);

    stream.writeStartDocument("1.0");
    stream.writeProcessingInstruction("mso-application progid", "Excel.Sheet");

    stream.writeStartElement("Workbook");
    stream.writeAttribute("xmlns", "urn:schemas-microsoft-com:office:spreadsheet");
    stream.writeAttribute("xmlns:o", "urn:schemas-microsoft-com:office:office");
    stream.writeAttribute("xmlns:x", "urn:schemas-microsoft-com:office:excel");
    stream.writeAttribute("xmlns:ss", "urn:schemas-microsoft-com:office:spreadsheet");
    stream.writeAttribute("xmlns:html", "http://www.w3.org/TR/REC-html40");

    stream.writeStartElement("Styles");
    stream.writeStartElement("Style");
    stream.writeAttribute("ss:ID", "Default");
    stream.writeAttribute("ss:Name", "Normal");
    stream.writeStartElement("Alignment");
    stream.writeAttribute("ss:Vertical", "Bottom");
    stream.writeEndElement();
    stream.writeEmptyElement("Borders");
    stream.writeEmptyElement("Font");
    stream.writeAttribute("ss:FontName", "Calibri");
    stream.writeAttribute("x:Family", "Swiss");
    stream.writeAttribute("ss:Size", "11");
    stream.writeAttribute("ss:Color", "#000000");
    stream.writeEmptyElement("Interior");
    stream.writeEmptyElement("NumberFormat");
    stream.writeEmptyElement("Protection");
    // </Style>

    stream.writeEndElement();
    // tag <Styles)
    stream.writeEndElement();

    stream.writeStartElement("Worksheet");
    stream.writeAttribute("ss:Name", QObject::tr("Sheet1"));

    stream.writeStartElement("Table");
    QPair<QModelIndex, QModelIndex> e;
    if (!all) {
        e = selectionEdges(view->selectionModel()->selection());
    } else {
        e.first = view->model()->index(0, 0);
        e.second = view->model()->index(view->model()->rowCount() - 1, view->model()->columnCount() - 1);
    }
    e.first = qSourceIndex(e.first);
    e.second = qSourceIndex(e.second);

    if (m_includeHeader) {
        stream.writeStartElement("Row");
        for (int c = e.first.column(); c <= e.second.column(); c++) {
            if (!view->horizontalHeader()->isSectionHidden(c)) {
                stream.writeStartElement("Cell");

                stream.writeStartElement("Data");
                stream.writeAttribute("ss:Type", "String");
                stream.writeCharacters(view->model()->headerData(view->horizontalHeader()->visualIndex(c), Qt::Horizontal, m_role).toString());
                // end tag <Data>
                stream.writeEndElement();
                // end tag <Cell>
                stream.writeEndElement();
            }
        }
        // end tag <Row>
        stream.writeEndElement();
    }
    for (int r = e.first.row(); r <= e.second.row(); r++) {
        stream.writeStartElement("Row");
        for (int c = e.first.column(); c <= e.second.column(); c++) {
            if (!view->horizontalHeader()->isSectionHidden(c)) {
                stream.writeStartElement("Cell");

                stream.writeStartElement("Data");
                stream.writeAttribute("ss:Type", "String");
                //l << "\"" + view->model()->index(r, view->horizontalHeader()->visualIndex(c)).data(Qt::DisplayRole).toString() + "\"";
                stream.writeCharacters(view->model()->index(r, view->horizontalHeader()->visualIndex(c)).data(m_role).toString());
                // end tag <Data>
                stream.writeEndElement();
                // end tag <Cell>
                stream.writeEndElement();
            }
        }
        // end tag <Row>
        stream.writeEndElement();
    }
    // end tag <Table>
    stream.writeEndElement();
    stream.writeEndElement();
    //
    stream.writeEndElement();
    return true;
}
