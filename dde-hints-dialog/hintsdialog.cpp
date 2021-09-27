/*
 * Copyright (C) 2020 ~ 2022 Uniontech Technology Co., Ltd.
 *
 * Author:     chenjun <chenjun@uniontech.com>
 *
 * Maintainer: chenjun <chenjun@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "hintsdialog.h"
#include "horizontalseperator.h"

#include <DFontSizeManager>

#include <QApplication>
#include <QIcon>
#include <QLabel>
#include <QLayout>


HintsDialog::HintsDialog(QWidget *parent)
    : DAbstractDialog(false, parent)
    , m_title(new QLabel(this))
    , m_content(new DTipLabel("", this))
    , m_closeButton(new DDialogCloseButton(this))
{
    setFixedWidth(windowFixedWidth);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    m_title->setObjectName("TitleLabel");
    m_title->setAccessibleName("TitleLabel");
    m_content->setAccessibleName("MainContent");

    DFontSizeManager::instance()->bind(m_title, DFontSizeManager::SizeType::T5, 70);

    m_closeButton->setIconSize(QSize(40, 40));

    m_content->setTextFormat(Qt::RichText);
    m_content->setAlignment(Qt::AlignJustify | Qt::AlignLeft);
    m_content->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_content->setWordWrap(true);

    QHBoxLayout *titlelayout = new QHBoxLayout;
    titlelayout->setMargin(0);
    titlelayout->setSpacing(0);
    titlelayout->addWidget(m_title, 1, Qt::AlignLeft | Qt::AlignVCenter);
    titlelayout->addWidget(m_closeButton, 0, Qt::AlignRight | Qt::AlignVCenter);

    QWidget *widget = new QWidget(this);
    widget->setAccessibleName("TitleWidget");
    widget->setFixedHeight(40);
    widget->setLayout(titlelayout);

    HorizontalSeperator * seperator = new HorizontalSeperator(this);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(15);
    layout->setSpacing(0);
    layout->addWidget(widget);
    layout->addSpacing(10);
    layout->addWidget(seperator);
    layout->addSpacing(10);
    layout->addWidget(m_content);
    setLayout(layout);

    connect(m_closeButton, &DDialogCloseButton::clicked, this, [ = ]{
        emit this->accept();
    });
}

HintsDialog::~HintsDialog()
{
}

void HintsDialog::setHintTitle(const QString &title)
{
    m_title->setText(title);
}

void HintsDialog::setHintContent(const QString &message)
{
    m_content->clear();
    m_content->adjustSize();
    m_content->setText(message);
    m_content->adjustSize();
    show();
}

void HintsDialog::showEvent(QShowEvent *event)
{
    moveToCenter();
    DAbstractDialog::showEvent(event);
}
