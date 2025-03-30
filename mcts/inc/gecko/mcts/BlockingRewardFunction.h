/*----------------------------------------------------------------------------*/
#ifndef GMDS_MCTS_BLOCKING_REWARD_FUNCTION_H
#define GMDS_MCTS_BLOCKING_REWARD_FUNCTION_H
/*----------------------------------------------------------------------------*/
#include <gecko/mcts/IRewardFunction.h>
/*----------------------------------------------------------------------------*/
namespace gecko {
/*----------------------------------------------------------------------------*/
namespace mctsc {
/*----------------------------------------------------------------------------*/
class BlockingRewardFunction: public IRewardFunction{

	double evaluate(std::shared_ptr<IState> AState) const override;

};
/*----------------------------------------------------------------------------*/
}     // namespace blocking
/*----------------------------------------------------------------------------*/
}     // namespace gmds
/*----------------------------------------------------------------------------*/
#endif     // GMDS_MCTS_BLOCKING_REWARD_FUNCTION_H
