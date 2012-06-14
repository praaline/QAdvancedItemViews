/*
 * This file is part of qadvanceditemviews.
 *
 * Copyright (c) 2011-2012 Martin Hoppe martin@2x2hoppe.de
 *
 * qadvanceditemviews is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General
 * Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any
 * later version.
 *
 * qadvanceditemviews is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with qadvanceditemviews.
 * If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QStandardItemModel;
class QGroupingProxyModel;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void aboutQtActionTriggered();
    void decoratedTableViewCustomContextMenuRequested(const QPoint & point);
    void decoratedGroupingTreeViewCustomContextMenuRequested(const QPoint & point);
    void exitActionTriggered();
    void groupWindowsCheckBoxToggled(bool on);
    void groupUnixCheckBoxToggled(bool on);

    void pinRowsToolButtonClicked();
    void populatePushButtonClicked();

    void splitActionTriggered();
private:
    void initModel();
    void initTabAdvancedTableView();
    void initTabConditionalDecorationProxyModel();
    void initTabGroupingProxyModel();
    void initTabConditionalDecorationAndGrouping();
    void initTabTableView();
    void initTabPinTableView();
    void initTabLargeTableView();

    void initTabUniqueValuesProxyModel();

    QGroupingProxyModel* m_groupingProxy;
    QStandardItemModel* m_model;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H