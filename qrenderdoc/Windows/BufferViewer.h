/******************************************************************************
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Baldur Karlsson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/

#pragma once

#include <QFrame>
#include "Code/CaptureContext.h"

namespace Ui
{
class BufferViewer;
}

class BufferItemModel;

class BufferViewer : public QFrame, public ILogViewerForm
{
  Q_OBJECT

public:
  explicit BufferViewer(CaptureContext *ctx, QWidget *parent = 0);
  ~BufferViewer();

  void OnLogfileLoaded();
  void OnLogfileClosed();
  void OnEventSelected(uint32_t eventID);

private slots:
  // automatic slots
  void on_outputTabs_currentChanged(int index);

  // manual slots
  void render_mouseMove(QMouseEvent *e);
  void render_clicked(QMouseEvent *e);
  void render_mouseWheel(QWheelEvent *e);
  void render_keyPress(QKeyEvent *e);
  void data_selected(const QItemSelection &selected, const QItemSelection &deselected);

private:
  Ui::BufferViewer *ui;
  CaptureContext *m_Ctx;

  IReplayOutput *m_Output;

  void RT_UpdateAndDisplay(IReplayRenderer *);

  MeshDisplay m_ConfigVSIn;
  MeshDisplay m_ConfigVSOut;
  MeshDisplay *m_curConfig;

  QPoint m_PrevPos;
  FloatVector m_pos, m_rot;
  float m_CamDist;

  BufferItemModel *m_ModelVSIn;
  BufferItemModel *m_ModelVSOut;
  // BufferItemModel *m_ModelGSOut;

  void Reset();
};
