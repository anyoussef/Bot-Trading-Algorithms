import { useEffect, useState } from "react";
import {
  getMAAccount,
  getRSIAccount,
  getMAPositions,
  getRSIPositions,
  getMAOrders,
  getRSIOrders,
  getClock,
} from "./api";
import StrategyCard from "./components/StrategyCard";

export default function App() {
  const [maAccount, setMAAccount] = useState(null);
  const [rsiAccount, setRSIAccount] = useState(null);
  const [maPositions, setMAPositions] = useState([]);
  const [rsiPositions, setRSIPositions] = useState([]);
  const [maOrders, setMAOrders] = useState([]);
  const [rsiOrders, setRSIOrders] = useState([]);
  const [clock, setClock] = useState<{
    is_open: boolean;
    next_open: string;
    next_close: string;
  } | null>(null);

  useEffect(() => {
    getMAAccount().then(setMAAccount);
    getRSIAccount().then(setRSIAccount);
    getMAPositions().then(setMAPositions);
    getRSIPositions().then(setRSIPositions);
    getMAOrders().then(setMAOrders);
    getRSIOrders().then(setRSIOrders);
    getClock().then(setClock);
  }, []);

  return (
    <div style={{ backgroundColor: "#1e1e2e" }} className="min-h-screen p-8">
      <h1 style={{ color: "#cba6f7" }} className="text-3xl font-bold mb-4">
        Bottrade Dashboard
      </h1>

      {clock && (
        <div
          style={{ color: clock.is_open ? "#a6e3a1" : "#f38ba8" }}
          className="text-sm mb-8"
        >
          Market is {clock.is_open ? "Open" : "Closed"} — Next open:{" "}
          {clock.next_open}
        </div>
      )}

      <div className="grid grid-cols-2 gap-6">
        <StrategyCard
          name="Moving Average"
          account={maAccount}
          positions={maPositions}
          orders={maOrders}
        />
        <StrategyCard
          name="RSI"
          account={rsiAccount}
          positions={rsiPositions}
          orders={rsiOrders}
        />
      </div>
    </div>
  );
}
