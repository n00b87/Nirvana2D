#include "NirvanaEngine_Structs.h"
#include <irrlicht.h>
#include <vector>

#include "rc_defines.h"



nirvana_stageAction current_action;

std::vector<nirvana_stageAction> undo_buffer;
std::vector<nirvana_stageAction> redo_buffer;


void push_undo(nirvana_stageAction n_action)
{
    if(undo_buffer.size() >= UNDO_REDO_BUFFER_SIZE)
    {
        std::vector<nirvana_stageAction> tmp_action;
        for(int i = 0; i < (undo_buffer.size()-1); i++)
        {
            tmp_action.push_back(undo_buffer[i+1]);
        }

        undo_buffer.clear();

        for(int i = 0; i < tmp_action.size(); i++)
        {
            undo_buffer.push_back(tmp_action[i]);
        }

        undo_buffer[undo_buffer.size()-1] = n_action;
    }
    else
    {
        undo_buffer.push_back(n_action);
    }

    current_action.action_type = -1;
    current_action.tiles.clear();
    current_action.sprite.clear();
}

nirvana_stageAction pop_undo()
{
    nirvana_stageAction n_action;

    if(undo_buffer.size() > 0)
    {
        n_action = undo_buffer[undo_buffer.size()-1];
        undo_buffer.erase(undo_buffer.begin() + undo_buffer.size()-1);
    }
    else
    {
        n_action.action_type = -1;
    }

    return n_action;
}

void clear_undo()
{
    undo_buffer.clear();
}


void push_redo(nirvana_stageAction n_action)
{
    if(redo_buffer.size() >= UNDO_REDO_BUFFER_SIZE)
    {
        std::vector<nirvana_stageAction> tmp_action;
        for(int i = 0; i < (redo_buffer.size()-1); i++)
        {
            tmp_action.push_back(redo_buffer[i+1]);
        }

        redo_buffer.clear();

        for(int i = 0; i < tmp_action.size(); i++)
        {
            redo_buffer.push_back(tmp_action[i]);
        }

        redo_buffer[redo_buffer.size()-1] = n_action;
    }
    else
    {
        redo_buffer.push_back(n_action);
    }

    current_action.action_type = -1;
    current_action.tiles.clear();
    current_action.sprite.clear();
}

nirvana_stageAction pop_redo()
{
    nirvana_stageAction n_action;

    if(redo_buffer.size() > 0)
    {
        n_action = redo_buffer[redo_buffer.size()-1];
        redo_buffer.erase(redo_buffer.begin() + redo_buffer.size()-1);
    }
    else
    {
        n_action.action_type = -1;
    }

    return n_action;
}

void clear_redo()
{
    redo_buffer.clear();
}
