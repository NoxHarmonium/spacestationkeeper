-- Mining Job
class 'WorkBot' (Bot)

WorkBot.States = {
    WAITING_FOR_JOB,
    
}

function WorkBot:__init(homeCoord)
    Bot.__init(self)
    LuaDebug.Log('WorkBot:__init() called!')
    self._homeCoord = homeCoord
    self._state = WorkBot.States.WAITING_FOR_JOB
    self._job = nil
    
end

function WorkBot:getDestination()
    if self._state == WorkBot.States.WAITING_FOR_JOB then
        return self._homeCoord;
    else 
    if self._state == WorkBot.States.MINING then
        if not self._job then error('ASSERT FAIL: In mining state without a job.') end
        return self._job:getStartLocation()
    end


end

function WorkBot:getSpeed()
    return 1.0
end

function WorkBot:willAcceptJob(job)
    return class_info(job).name == 'MiningJob' 
end

function WorkBot:acceptJob(job)
    _self._job = job
end