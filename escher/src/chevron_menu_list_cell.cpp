#include <escher/chevron_menu_list_cell.h>

ChevronMenuListCell::ChevronMenuListCell(char * label, KDText::FontSize size) :
  MenuListCell(label, size),
  m_accessoryView(ChevronView())
{
}

View * ChevronMenuListCell::accessoryView() const {
  return (View *)&m_accessoryView;
}

void ChevronMenuListCell::setHighlighted(bool highlight) {
  MenuListCell::setHighlighted(highlight);
  m_accessoryView.setHighlighted(isHighlighted());
}
