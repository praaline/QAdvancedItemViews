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
#ifndef QTABLEMODELCSVWRITER_P_H
#define QTABLEMODELCSVWRITER_P_H

class QAdvancedTableView;
class QIODevice;
class QTableView;

class QTableModelCsvWriter
{
public:
    QTableModelCsvWriter(QIODevice* device);
    ~QTableModelCsvWriter();

    bool writeAll(QAdvancedTableView* view, bool all);

    bool writeAll(QTableView* view, bool all);
private:
    QIODevice* m_device;
};

#endif // QTABLEMODELCSVWRITER_P_H
