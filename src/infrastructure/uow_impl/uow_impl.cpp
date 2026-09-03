#include "uow_impl/uow_impl.h"

using namespace infrastructure;

void infrastructure::Uow::commit() {
    work_.commit();
}
