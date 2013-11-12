#ifndef MUTRADEAPI_TRADE_BOOK_H
#define MUTRADEAPI_TRADE_BOOK_H

#include <map>
#include <list>

#include "types.h"
#include "trade.h"

namespace mutrade {

  /**
   *
   * \brief TradeBook class
   *
   * This class stores the list of all the trades which have happened during
   * the day.
   *
   * \note The trades which happened before the connection was
   * made can be replayed back from the server and this class will then be
   * able to serve the list of all trades happened during the day.
   *
   */

  class TradeBook
  {
    typedef std::list<Trade*> TradeList;
    /**
     * Each ClOrderId is mapped to the list of trades which have happened
     * for that particular ClOrderId
     */
    typedef std::map<Int64, TradeList> TradeBookMap;
    typedef std::map<Int64, TradeList>::iterator TradeBookMapIter;
    typedef std::map<Int64, TradeList>::iterator TradeBookMapCIter;

 public:
    /**
     * \brief Get List of trades
     *
     * \param clOrderId (client order ID generated by the server)
     */
    TradeList* getTrades(Int64 clOrderId) throw (std::domain_error);

    /**
     * \brief Updates the trade in the TradeBook
     *
     * This method updates the trades which are receieved as executions
     * from the exchange.
     *
     * \note The user of the API does not need to call this
     * method. It is called by the API automatically when an execution is
     * received.
     */
    int update(ExecutionReport& report);

  private:

    void insertTrade(Trade* trade);

    TradeBookMap _tradeBook;
  };

} // namespace mutrade
#endif
