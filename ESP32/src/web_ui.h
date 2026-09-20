#pragma once

const char INDEX_HTML[] PROGMEM = R"rawlLiteral(
<!doctype html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>OreX Rover</title>
    <style>
      :root {
        --bg: #081821;
        --bg-2: #0f2533;
        --panel: rgba(18, 36, 45, 0.9);
        --panel-alt: rgba(24, 47, 58, 0.9);
        --line: rgba(148, 163, 184, 0.2);
        --text: #eaf6ff;
        --muted: #9db6c7;
        --cyan: #38bdf8;
        --green: #4ade80;
        --amber: #fbbf24;
        --red: #f87171;
        --purple: #a78bfa;
        --shadow: 0 18px 42px rgba(8, 24, 33, 0.45);
      }

      * { box-sizing: border-box; }

      body {
        margin: 0;
        font-family: Inter, "Segoe UI", sans-serif;
        background:
          radial-gradient(circle at top left, rgba(56, 189, 248, 0.18), transparent 30%),
          radial-gradient(circle at bottom right, rgba(74, 222, 128, 0.12), transparent 25%),
          linear-gradient(135deg, var(--bg), var(--bg-2));
        color: var(--text);
      }

      .app {
        max-width: 1180px;
        margin: 0 auto;
        padding: 32px 20px 50px;
      }

      .topbar {
        display: flex;
        align-items: center;
        justify-content: space-between;
        gap: 20px;
        margin-bottom: 28px;
        padding: 18px 22px;
        background: rgba(15, 37, 51, 0.8);
        border: 1px solid var(--line);
        border-radius: 18px;
        box-shadow: var(--shadow);
      }

      .brand {
        display: flex;
        align-items: center;
        gap: 14px;
      }

      .brand-mark {
        width: 46px;
        height: 46px;
        border-radius: 14px;
        display: grid;
        place-items: center;
        font-weight: 800;
        background: linear-gradient(135deg, var(--cyan), var(--green));
        color: #06131c;
      }

      .brand h1 {
        margin: 0;
        font-size: clamp(1.6rem, 2vw, 2.4rem);
        letter-spacing: 0.04em;
      }

      .pill {
        display: inline-flex;
        align-items: center;
        gap: 8px;
        background: rgba(56, 189, 248, 0.12);
        border: 1px solid rgba(56, 189, 248, 0.28);
        padding: 9px 14px;
        border-radius: 999px;
        color: var(--cyan);
        font-weight: 700;
        font-size: 0.82rem;
      }

      .grid {
        display: grid;
        grid-template-columns: repeat(4, minmax(180px, 1fr));
        gap: 18px;
        margin-bottom: 24px;
      }

      .card {
        background: linear-gradient(180deg, var(--panel), var(--panel-alt));
        border: 1px solid var(--line);
        border-radius: 18px;
        padding: 18px 18px 16px;
        box-shadow: var(--shadow);
      }

      .status-card {
        display: flex;
        flex-direction: column;
        justify-content: space-between;
        min-height: 160px;
      }

      .label {
        font-size: 0.78rem;
        letter-spacing: 0.12em;
        text-transform: uppercase;
        color: var(--muted);
      }

      .value {
        font-size: clamp(2rem, 3vw, 3rem);
        font-weight: 800;
        margin-top: 12px;
      }

      .subtext {
        margin-top: 8px;
        color: var(--muted);
        font-size: 0.92rem;
      }

      .mode-auto { color: var(--green); }
      .mode-manual { color: var(--amber); }
      .mode-stop { color: var(--red); }
      .mode-bad { color: var(--red); }

      .card-title {
        margin: 0 0 16px;
        font-size: 1.1rem;
      }

      .controls {
        display: grid;
        grid-template-columns: 1.3fr 2fr;
        gap: 18px;
        margin-bottom: 24px;
      }

      .button-stack {
        display: grid;
        grid-template-columns: 1fr 1fr;
        gap: 12px;
      }

      button {
        border: 0;
        border-radius: 14px;
        padding: 14px 18px;
        font-size: 0.98rem;
        font-weight: 800;
        letter-spacing: 0.05em;
        cursor: pointer;
        background: rgba(148, 163, 184, 0.14);
        color: var(--text);
        transition: transform 0.15s ease, opacity 0.15s ease;
      }

      button:hover {
        transform: translateY(-1px);
        opacity: 0.96;
      }

      .primary {
        background: linear-gradient(135deg, #22c55e, #16a34a);
        color: #03150b;
      }

      .danger {
        background: linear-gradient(135deg, #f87171, #ef4444);
        color: #fff;
      }

      .alarm {
        background: linear-gradient(135deg, #fbbf24, #f97316);
        color: #241000;
      }

      .alarm.active {
        background: linear-gradient(135deg, #ef4444, #b91c1c);
        color: #fff;
      }

      .control-grid {
        display: grid;
        grid-template-columns: repeat(3, minmax(0, 1fr));
        grid-template-areas:
          ". forward ."
          "left . right"
          ". backward .";
        gap: 10px;
      }

      .dir-btn {
        background: rgba(56, 189, 248, 0.14);
        border: 1px solid rgba(56, 189, 248, 0.25);
        color: var(--text);
      }

      .dir-btn { min-width: 0; touch-action: none; }
      .dir-btn[data-cmd="forward"] { grid-area: forward; }
      .dir-btn[data-cmd="left"] { grid-area: left; }
      .dir-btn[data-cmd="right"] { grid-area: right; }
      .dir-btn[data-cmd="backward"] { grid-area: backward; }

      .sensor-grid {
        display: grid;
        grid-template-columns: repeat(5, minmax(150px, 1fr));
        gap: 18px;
        margin-bottom: 24px;
      }

      .metric {
        min-height: 150px;
      }

      .metric .value {
        font-size: clamp(1.4rem, 2vw, 2.3rem);
      }

      .metric .unit {
        display: block;
        margin-top: 8px;
        color: var(--muted);
        font-size: 0.86rem;
      }

      .raw-panel {
        padding: 16px 18px 18px;
      }

      pre {
        margin: 12px 0 0;
        white-space: pre-wrap;
        word-break: break-word;
        padding: 14px 16px;
        border-radius: 12px;
        background: rgba(8, 24, 33, 0.8);
        border: 1px solid var(--line);
        color: var(--text);
        min-height: 220px;
        overflow: auto;
      }

      @media (max-width: 900px) {
        .grid, .sensor-grid, .controls {
          grid-template-columns: 1fr 1fr;
        }
      }

      @media (max-width: 640px) {
        .app {
          padding-left: 14px;
          padding-right: 14px;
        }

        .topbar, .grid, .sensor-grid, .controls {
          grid-template-columns: 1fr;
          display: grid;
        }

        .button-stack {
          grid-template-columns: 1fr 1fr;
        }

        .control-grid {
          gap: 8px;
        }

        .dir-btn {
          padding-left: 6px;
          padding-right: 6px;
          font-size: 0.8rem;
          letter-spacing: 0.02em;
        }
      }
    </style>
  </head>
  <body>
    <div class="app">
      <header class="topbar">
        <div class="brand">
          <div class="brand-mark">O</div>
          <div>
            <h1>OreX Rover</h1>
          </div>
        </div>
        <div class="pill">AP: OreX-Rover • 192.168.4.1</div>
      </header>

      <section class="grid">
        <div class="card status-card">
          <div class="label">System Mode</div>
          <div id="mode" class="value mode-stop">STOP</div>
          <div id="modeText" class="subtext">Standby</div>
        </div>

        <div class="card status-card">
          <div class="label">Obstacle</div>
          <div id="obstacle" class="value mode-bad">NO</div>
          <div id="distance" class="subtext">Distance: -- cm</div>
        </div>

        <div class="card status-card">
          <div class="label">Temperature</div>
          <div id="temperature" class="value">--</div>
          <div class="subtext">°C</div>
        </div>

        <div class="card status-card">
          <div class="label">Humidity</div>
          <div id="humidity" class="value">--</div>
          <div class="subtext">%</div>
        </div>
      </section>

      <section class="controls">
        <div class="card">
          <h2 class="card-title">Drive Controls</h2>
          <div class="button-stack">
            <button class="primary" data-cmd="auto">AUTO</button>
            <button class="danger" data-cmd="stop">STOP</button>
            <button class="alarm" data-cmd="alarm" aria-pressed="false">ALARM</button>
          </div>
        </div>

        <div class="card">
          <h2 class="card-title">Manual Drive</h2>
          <div class="control-grid">
            <button class="dir-btn" data-cmd="forward" data-drive>FORWARD</button>
            <button class="dir-btn" data-cmd="left" data-drive>LEFT</button>
            <button class="dir-btn" data-cmd="right" data-drive>RIGHT</button>
            <button class="dir-btn" data-cmd="backward" data-drive>BACKWARD</button>
          </div>
          <div class="subtext">PIR motion sensing works only while the rover is at HALT.</div>
        </div>
      </section>

      <section class="sensor-grid">
        <div class="card metric">
          <div class="label">MQ2</div>
          <div id="mq2" class="value">--</div>
          <span class="unit">Gas Index</span>
        </div>

        <div class="card metric">
          <div class="label">MQ4</div>
          <div id="mq4" class="value">--</div>
          <span class="unit">Gas Index</span>
        </div>

        <div class="card metric">
          <div class="label">MQ7</div>
          <div id="mq7" class="value">--</div>
          <span class="unit">Gas Index</span>
        </div>

        <div class="card metric">
          <div class="label">Uptime</div>
          <div id="uptime" class="value">--</div>
          <span class="unit">ms</span>
        </div>

        <div class="card metric">
          <div class="label">Status</div>
          <div id="status" class="value">OK</div>
          <span class="unit">Live</span>
        </div>

        <div class="card metric">
          <div class="label">PIR Motion</div>
          <div id="pir" class="value">OFF</div>
          <span class="unit">Halt only</span>
        </div>
      </section>

      <div class="card raw-panel">
        <h2 class="card-title">Live Telemetry</h2>
        <pre id="rawData">Loading...</pre>
      </div>
    </div>

    <script>
      const modeEl = document.getElementById('mode');
      const modeTextEl = document.getElementById('modeText');
      const obstacleEl = document.getElementById('obstacle');
      const distanceEl = document.getElementById('distance');
      const tempEl = document.getElementById('temperature');
      const humidityEl = document.getElementById('humidity');
      const rawDataEl = document.getElementById('rawData');
      const mq2El = document.getElementById('mq2');
      const mq4El = document.getElementById('mq4');
      const mq7El = document.getElementById('mq7');
      const uptimeEl = document.getElementById('uptime');
      const statusEl = document.getElementById('status');
      const pirEl = document.getElementById('pir');
      const alarmButton = document.querySelector('[data-cmd="alarm"]');
      let driveTimer;

      function setMode(mode) {
        const value = String(mode || 'stop').toUpperCase();
        modeEl.textContent = value;
        modeEl.classList.remove('mode-auto', 'mode-manual', 'mode-stop');

        if (value === 'AUTO') {
          modeEl.classList.add('mode-auto');
          modeTextEl.textContent = 'Autonomous navigation active';
        } else if (value === 'MANUAL') {
          modeEl.classList.add('mode-manual');
          modeTextEl.textContent = 'Operator control active';
        } else {
          modeEl.classList.add('mode-stop');
          modeTextEl.textContent = 'System halted';
        }
      }

      function updateStatus(data) {
        if (typeof data.temperatureC === 'number') {
          tempEl.textContent = data.temperatureC.toFixed(1);
        } else {
          tempEl.textContent = 'N/A';
        }

        if (typeof data.humidity === 'number') {
          humidityEl.textContent = data.humidity.toFixed(1);
        } else {
          humidityEl.textContent = 'N/A';
        }

        if (typeof data.distanceCm === 'number') {
          distanceEl.textContent = 'Distance: ' + data.distanceCm + ' cm';
          obstacleEl.textContent = data.obstacle ? 'YES' : 'NO';
          obstacleEl.classList.toggle('mode-bad', !!data.obstacle);
          obstacleEl.classList.toggle('mode-auto', !data.obstacle);
        }

        mq2El.textContent = data.mq2 ?? '--';
        mq4El.textContent = data.mq4 ?? '--';
        mq7El.textContent = data.mq7 ?? '--';
        uptimeEl.textContent = data.uptimeMs ?? '--';
        pirEl.textContent = data.pirEnabled ? (data.pirMotion ? 'MOTION' : 'CLEAR') : 'HALT ONLY';
        pirEl.classList.toggle('mode-bad', !!data.pirMotion);
        alarmButton.classList.toggle('active', !!data.alarmEnabled);
        alarmButton.setAttribute('aria-pressed', String(!!data.alarmEnabled));
        alarmButton.textContent = data.alarmEnabled ? 'ALARM ON' : 'ALARM';

        if (data.obstacle) {
          statusEl.textContent = 'ALERT';
          statusEl.classList.add('mode-bad');
        } else {
          statusEl.textContent = 'OK';
          statusEl.classList.remove('mode-bad');
        }

        if (data.pirEnabled && data.pirMotion) {
          statusEl.textContent = 'MOTION';
          statusEl.classList.add('mode-bad');
        }
      }

      async function cmd(command) {
        try {
          const response = await fetch('/api/command?cmd=' + command, { method: 'POST' });
          if (!response.ok) throw new Error(await response.text());
          if (command === 'alarm') await loadData();
        } catch (error) {
          rawDataEl.textContent = 'Command failed: ' + error.message;
        }
      }

      async function loadData() {
        try {
          const resp = await fetch('/api/data');
          const data = await resp.json();
          setMode(data.mode);
          updateStatus(data);
          rawDataEl.textContent = JSON.stringify(data, null, 2);
        } catch (error) {
          rawDataEl.textContent = 'Unable to fetch sensor data.';
        }
      }

      document.querySelectorAll('[data-drive]').forEach((button) => {
        const startDrive = (event) => {
          event.preventDefault();
          button.setPointerCapture(event.pointerId);
          clearInterval(driveTimer);
          cmd(button.dataset.cmd);
          driveTimer = setInterval(() => cmd(button.dataset.cmd), 250);
        };
        const stopDrive = (event) => {
          event.preventDefault();
          clearInterval(driveTimer);
          driveTimer = undefined;
          cmd('stop');
        };
        button.addEventListener('pointerdown', startDrive);
        button.addEventListener('pointerup', stopDrive);
        button.addEventListener('pointercancel', stopDrive);
      });

      document.querySelectorAll('[data-cmd]:not([data-drive])').forEach((button) => {
        button.addEventListener('click', () => cmd(button.dataset.cmd));
      });

      setInterval(loadData, 2000);
      loadData();
    </script>
  </body>
</html>
)rawlLiteral";
