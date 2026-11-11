# Cold Cell Design Notebook
Entries go newest at the bottom.

---

# Session Entry Template
Copy this for every session.

## <Session code> — <title>        Date:        Time: start-end

Goal:

Requirements touched: R__

Predictions (write these BEFORE you start):

Setup: (photo filename, firmware commit)

What I did: (numbered steps, exactly)

What I observed: (numbers with units; data file names)

Results: (computed values with uncertainty)

Did it match my prediction? (by how much, and why not)

Anomalies:

Conclusion (1-2 sentences):

Next action:

Explain-back (3 sentences from memory, no notes):

---
## SETUP — Toolchain and repo        Date: 2026-11-11        Time: 10:00-11:30

Goal: Set up the toolchain and the project repo.

Requirements touched: None (setup session)

Predictions (write these BEFORE you start): None (setup session)

Setup: No photo (software only). Repo commit: [937555a --oneline -1]. No firmware yet.

What I did:
1. Installed Python with numpy, pandas, matplotlib, pyserial.
2. Installed WSL with Ubuntu, then build-essential (gcc), git, and gh.
3. Installed STM32CubeIDE and LTspice.
4. Authenticated GitHub from Ubuntu with gh auth login, entering the device code in my Windows browser because WSL has no browser.
5. Set my git identity (user.name and user.email).
6. In the existing cold-cell repo, created the blueprint folder structure, the five docs files, .gitkeep placeholders, and a .gitignore.
7. Resolved a rebase conflict on docs/notebook.md after a rejected push, then pushed.
8. Reset docs/notebook.md with the session template and pushed again.
9. Built the co-op application tracker with 13 target companies.

What I observed:
- Two pushes were rejected with "fetch first" (GitHub had commits my laptop lacked).
- git pull --rebase stopped on a conflict in docs/notebook.md.
- First successful push: b0d3807..4846450 main -> main.
- Tracker has 13 companies (5 Tier A, 4 Tier B, 4 Tier C).
- No data files today.

Results: Repo synced with GitHub, working tree clean. Toolchain installed and verified. No measured values, so no uncertainty.

Did it match my prediction? No predictions written. The blueprint estimated 40 min for setup; it took 1.5 hours because of WSL, authentication, and merge problems.

Anomalies:
- "sudo: not recognized" because I was in PowerShell, not Ubuntu.
- Browser failed to open during gh auth login (WSL has no browser).
- Stuck in a heredoc after pasting commands together.
- "Author identity unknown" on the first commit.
- Two rejected pushes and one notebook.md merge conflict.
- Ran commands from my home folder instead of the repo several times.

Conclusion: The toolchain and repo are ready for D1 on Saturday. Most of the time went on Git and WSL problems rather than installation.

Next action: Thu Nov 12: check the five Tier A careers pages, set job alerts, and read E1 chapter 1. Verify the careers-page links in the tracker.

Explain-back: sudo and apt only exist in Ubuntu, so PowerShell said "not recognized," and WSL has no browser, so I entered the gh login code manually at github.com/login/device. My pushes were rejected because GitHub already had commits my laptop lacked, and git pull --rebase then stopped on a conflict because notebook.md had changed on both sides, so I chose which version to keep and ran git rebase --continue. I also kept running commands from my home folder instead of cold-cell, so I should check pwd first.
