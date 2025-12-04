--CAN bus
---For OBDII operation, ensure the CAN bus is set to On.
---Common baud rates for OBDII are 500K and 250K. The default is 500K, which applies to nearly every CAN OBDII vehicle. AIM CAN is 1M.

local counter = 0
local lastTime = 0

function onTick()
    local now = getUptime()
    if now - lastTime > 0.10 then--every 100 ms
        lastTime = now

        counter = (counter + 1) % 256   -- keep it 0–255

        txCAN(0, 0x100, 0, 1, {counter})
    end
end
