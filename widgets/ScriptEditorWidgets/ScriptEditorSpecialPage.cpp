/****************************************************************************
 ** Makou Reactor Final Fantasy VII Field Script Editor
 ** Copyright (C) 2009-2020 Arzel Jérôme <myst6re@gmail.com>
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/
#include "ScriptEditorSpecialPage.h"

ScriptEditorDLPBSavemap::ScriptEditorDLPBSavemap(Field *field, GrpScript *grpScript,
                                         Script *script, int opcodeID,
                                         QWidget *parent) :
    ScriptEditorView(field, grpScript, script, opcodeID, parent)
{
}

void ScriptEditorDLPBSavemap::build()
{
	_from = new QSpinBox(this);
	_from->setRange(0, 65535);
	_to = new QSpinBox(this);
	_to->setRange(0, 65535);
	_absValue = new QDoubleSpinBox(this);
	_absValue->setDecimals(0);
	_absValue->setRange(0, pow(2, 32)-1);

	_flag = new QComboBox(this);
	_flag->addItem("-");
	_flag->addItem(tr("8 bit"));
	_flag->addItem(tr("16 bit"));
	_flag->addItem(tr("24 bit"));
	_flag->addItem(tr("32 bit"));

	_fromIsPointer = new QCheckBox(tr("From is a pointer"), this);
	_toIsPointer = new QCheckBox(tr("To is a pointer"), this);

	QGridLayout *layout = new QGridLayout(this);
	layout->addWidget(new QLabel(tr("From")), 0, 0);
	layout->addWidget(_from, 0, 1, 1, 3);
	layout->addWidget(new QLabel(tr("To")), 1, 0);
	layout->addWidget(_to, 1, 1, 1, 3);
	layout->addWidget(new QLabel(tr("Abs Value")), 2, 0);
	layout->addWidget(_absValue, 2, 1, 1, 3);
	layout->addWidget(new QLabel(tr("Size")), 3, 0);
	layout->addWidget(_flag, 3, 1, 1, 3);
	layout->addWidget(_fromIsPointer, 4, 0, 1, 2);
	layout->addWidget(_toIsPointer, 4, 2, 1, 2);
	layout->setRowStretch(5, 1);
	layout->setColumnStretch(2, 1);
	layout->setContentsMargins(QMargins());

	connect(_from, SIGNAL(editingFinished()), SIGNAL(opcodeChanged()));
	connect(_to, SIGNAL(editingFinished()), SIGNAL(opcodeChanged()));
	connect(_absValue, SIGNAL(editingFinished()), SIGNAL(opcodeChanged()));
	connect(_flag, SIGNAL(currentIndexChanged(int)), SIGNAL(opcodeChanged()));
	connect(_fromIsPointer, SIGNAL(toggled(bool)), SIGNAL(opcodeChanged()));
	connect(_toIsPointer, SIGNAL(toggled(bool)), SIGNAL(opcodeChanged()));
}

Opcode *ScriptEditorDLPBSavemap::opcode()
{
	Opcode1A *opcode = (Opcode1A *)opcodePtr();

	opcode->from = quint16(_from->value());
	opcode->to = quint16(_to->value());
	opcode->absValue = quint32(_absValue->value());
	opcode->flag = quint8((_toIsPointer->isChecked() << 5) |
	                      (_fromIsPointer->isChecked() << 4) |
	                      quint8(_flag->currentIndex()));

	return opcodePtr();
}

void ScriptEditorDLPBSavemap::setOpcode(Opcode *opcode)
{
	ScriptEditorView::setOpcode(opcode);

	Opcode1A *o = (Opcode1A *)opcode;

	_from->setValue(o->from);
	_to->setValue(o->to);
	_absValue->setValue(o->absValue);
	_flag->setCurrentIndex(o->flag & 0x7);
	_fromIsPointer->setChecked(o->flag & 0x10);
	_toIsPointer->setChecked(o->flag & 0x20);
}

ScriptEditorDLPBWriteToMemory::ScriptEditorDLPBWriteToMemory(Field *field, GrpScript *grpScript,
                                                 Script *script, int opcodeID,
                                                 QWidget *parent) :
      ScriptEditorView(field, grpScript, script, opcodeID, parent)
{
}

void ScriptEditorDLPBWriteToMemory::build()
{
	_address = new QDoubleSpinBox(this);
	_address->setDecimals(0);
	_address->setRange(0, pow(2, 32)-1);
	_bytes = new QLineEdit(this);

	QGridLayout *layout = new QGridLayout(this);
	layout->addWidget(new QLabel(tr("Address")), 0, 0);
	layout->addWidget(_address, 0, 1, 1, 3);
	layout->addWidget(new QLabel(tr("Bytes")), 1, 0);
	layout->addWidget(_bytes, 1, 1, 1, 3);
	layout->setRowStretch(2, 1);
	layout->setContentsMargins(QMargins());

	connect(_address, SIGNAL(editingFinished()), SIGNAL(opcodeChanged()));
	connect(_bytes, SIGNAL(editingFinished()), SIGNAL(opcodeChanged()));
}

Opcode *ScriptEditorDLPBWriteToMemory::opcode()
{
	Opcode1C *opcode = (Opcode1C *)opcodePtr();

	opcode->address = quint32(_address->value());
	opcode->bytes = QByteArray::fromHex(_bytes->text().toLatin1());

	return opcodePtr();
}

void ScriptEditorDLPBWriteToMemory::setOpcode(Opcode *opcode)
{
	ScriptEditorView::setOpcode(opcode);

	Opcode1C *o = (Opcode1C *)opcode;

	_address->setValue(o->address);
	_bytes->setText(o->bytes.toHex());
}
