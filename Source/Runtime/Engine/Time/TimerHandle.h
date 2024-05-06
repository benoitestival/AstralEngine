#pragma once


struct FTimerHandle {
public:
    int TimerId;
};

template <>
struct std::hash<FTimerHandle>{
    std::size_t operator()(const FTimerHandle Handle) const noexcept {
        return std::hash<int>()(Handle.TimerId);
    }
};
