--CAN bus
---For OBDII operation, ensure the CAN bus is set to On.
---Common baud rates for OBDII are 500K and 250K. The default is 500K, which applies to nearly every CAN OBDII vehicle. AIM CAN is 1M.

local counter = 0
local lastTime = 0

local channel = 1
local id = 40 --idk what to put here. I don't think id matters
local command = 0 --I think this tells it to send a normal can message. I'm still looking for better documentation


function onTick()
    local now = getUptime()
    if now - lastTime > 0.10 then--every 100 ms
        lastTime = now

        counter = (counter + 1) % 256   -- keep it 0–255
        

        txCAN(channel, id, command, {0, 1, counter})
        
    end
end
