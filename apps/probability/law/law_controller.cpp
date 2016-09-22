#include "law_controller.h"
#include <assert.h>
#include "../app.h"

static const char * sMessages[] = {
  "Loi Normale",
  "Exponentielle",
  "Student",
  "Khi 2",
  "Binomiale",
  "Poisson",
  "Geometrique"
};

Probability::LawController::LawController(Responder * parentResponder) :
  ViewController(parentResponder),
  m_tableView(TableView(this, Metric::TopMargin, Metric::RightMargin,
    Metric::BottomMargin, Metric::LeftMargin)),
  m_activeCell(0)
{
  m_messages = sMessages;
}

View * Probability::LawController::view() {
  return &m_tableView;
}

const char * Probability::LawController::title() const {
  return "Type de Loi";
}

void Probability::LawController::setActiveCell(int index) {
  if (index < 0 || index >= k_totalNumberOfModels) {
    return;
  }

  m_activeCell = index;
  m_tableView.scrollToRow(index);
  LawCell * cell = (LawCell *)(m_tableView.cellAtIndex(index));
  cell->setParentResponder(this);
  app()->setFirstResponder(cell);
}

bool Probability::LawController::handleEvent(Ion::Events::Event event) {
  switch (event) {
    case Ion::Events::Event::DOWN_ARROW:
      setActiveCell(m_activeCell+1);
      return true;
    case Ion::Events::Event::UP_ARROW:
      setActiveCell(m_activeCell-1);
      return true;
    case Ion::Events::Event::ENTER:
      ((Probability::App *)app())->setLaw(App::Law::Normal);
      return true;
    default:
      return false;
  }
}

int Probability::LawController::numberOfCells() {
  return k_totalNumberOfModels;
};

View * Probability::LawController::reusableCell(int index) {
  assert(index >= 0);
  assert(index < k_maxNumberOfCells);
  return &m_cells[index];
}

int Probability::LawController::reusableCellCount() {
  return k_maxNumberOfCells;
}

void Probability::LawController::willDisplayCellForIndex(View * cell, int index) {
  LawCell * myCell = (LawCell *)cell;
  myCell->setMessage(m_messages[index]);
  myCell->setEven(index%2 == 0);
}

KDCoordinate Probability::LawController::cellHeight() {
  return 35;
}
