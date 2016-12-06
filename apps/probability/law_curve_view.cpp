#include "law_curve_view.h"
#include <assert.h>

namespace Probability {

LawCurveView::LawCurveView(Law * law) :
  CurveView(),
  m_law(law)
{
}

void LawCurveView::reload() {
  markRectAsDirty(bounds());
  computeLabels(Axis::Horizontal);
}

void LawCurveView::drawRect(KDContext * ctx, KDRect rect) const {
  ctx->fillRect(bounds(), KDColorWhite);
  drawAxes(Axis::Horizontal, ctx, rect);
  drawLabels(Axis::Horizontal, ctx, rect);
  drawExpression(m_law->expression(), KDColorRed, ctx, rect);
}

float LawCurveView::min(Axis axis) const {
  assert(axis == Axis::Horizontal || axis == Axis::Vertical);
  return (axis == Axis::Horizontal ? m_law->xMin() : m_law->yMin());
}

float LawCurveView::max(Axis axis) const {
  assert(axis == Axis::Horizontal || axis == Axis::Vertical);
  return (axis == Axis::Horizontal ? m_law->xMax() : m_law->yMax());
}

float LawCurveView::scale(Axis axis) const {
  assert(axis == Axis::Horizontal);
  return m_law->scale();
}

char * LawCurveView::label(Axis axis, int index) const {
  assert(axis == Axis::Horizontal);
  return (char *)m_labels[index];
}

float LawCurveView::evaluateExpressionAtAbscissa(Expression * expression, float abscissa) const {
  m_law->evaluateContext()->setOverridenValueForSymbolT(abscissa);
  return expression->approximate(*(m_law->evaluateContext()));
}

}
