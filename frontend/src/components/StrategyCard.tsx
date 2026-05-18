interface Props {
  name: string;
  account: {
    account_number: string;
    cash: string;
    portfolio_value: string;
  } | null;
  positions: {
    symbol: string;
    shares: number;
    market_value: string;
    unrealized_pl: string;
  }[];
  orders: {
    symbol: string;
    status: string;
    side: string;
  }[];
}

export default function StrategyCard({
  name,
  account,
  positions,
  orders,
}: Props) {
  return (
    <div
      style={{ backgroundColor: "#313244" }}
      className="rounded-2xl p-6 flex flex-col gap-4"
    >
      <h2 style={{ color: "#cba6f7" }} className="text-xl font-bold">
        {name}
      </h2>

      {account && (
        <div className="flex flex-col gap-1">
          <p style={{ color: "#89b4fa" }} className="text-sm">
            Account: {account.account_number.slice(0, 6) + "**********"}
          </p>
          <p style={{ color: "#cdd6f4" }} className="text-sm">
            Cash: ${parseFloat(account.cash).toLocaleString()}
          </p>
          <p style={{ color: "#cdd6f4" }} className="text-sm">
            Portfolio: ${parseFloat(account.portfolio_value).toLocaleString()}
          </p>
        </div>
      )}

      <div>
        <h3 style={{ color: "#f9e2af" }} className="text-sm font-semibold mb-2">
          Positions
        </h3>
        {positions.length === 0 ? (
          <p style={{ color: "#6c7086" }} className="text-sm">
            No open positions
          </p>
        ) : (
          positions.map((p) => (
            <div
              key={p.symbol}
              className="flex justify-between text-sm"
              style={{ color: "#cdd6f4" }}
            >
              <span>{p.symbol}</span>
              <span>{p.shares} shares</span>
              <span
                style={{
                  color:
                    parseFloat(p.unrealized_pl) >= 0 ? "#a6e3a1" : "#f38ba8",
                }}
              >
                ${p.unrealized_pl}
              </span>
            </div>
          ))
        )}
      </div>

      <div>
        <h3 style={{ color: "#f9e2af" }} className="text-sm font-semibold mb-2">
          Orders
        </h3>
        {orders.length === 0 ? (
          <p style={{ color: "#6c7086" }} className="text-sm">
            No pending orders
          </p>
        ) : (
          orders.map((o, i) => (
            <div
              key={i}
              className="flex justify-between text-sm"
              style={{ color: "#cdd6f4" }}
            >
              <span>{o.symbol}</span>
              <span style={{ color: o.side === "buy" ? "#a6e3a1" : "#f38ba8" }}>
                {o.side}
              </span>
              <span style={{ color: "#6c7086" }}>{o.status}</span>
            </div>
          ))
        )}
      </div>
    </div>
  );
}
