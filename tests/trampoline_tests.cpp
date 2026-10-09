#include <SKSE/Trampoline.h>

TEST_CASE("Two distinct call hooks fit in one 28-byte trampoline") {
    alignas(16) std::array<std::byte, 64> memory{};
    memory[0] = std::byte{0xE8};
    memory[8] = std::byte{0xE8};
    const auto base = reinterpret_cast<std::uintptr_t>(memory.data());

    auto trampoline = SKSE::Trampoline("EquipmentCycleHotkeys hook budget test");
    trampoline.set_trampoline(memory.data() + 16, 28);
    REQUIRE(trampoline.write_call<5>(base, base + 48) == base + 5);
    REQUIRE(trampoline.allocated_size() == 14);
    REQUIRE(trampoline.write_call<5>(base + 8, base + 56) == base + 13);
    REQUIRE(trampoline.allocated_size() == 28);
    REQUIRE(trampoline.free_size() == 0);
}
