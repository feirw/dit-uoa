document.addEventListener('DOMContentLoaded', () => {
    if (typeof hljs !== 'undefined') {
        hljs.highlightAll();
    }

    initCopyButtons();
    initSidebarScroll();
});

function initCopyButtons() {
    document.querySelectorAll('.copy-btn').forEach(btn => {
        btn.addEventListener('click', () => {
            const wrapper = btn.closest('.code-wrapper') || btn.closest('.query-card');
            if (!wrapper) return;

            const code = wrapper.querySelector('code');
            if (!code) return;

            navigator.clipboard.writeText(code.textContent).then(() => {
                btn.textContent = 'Copied';
                btn.classList.add('copied');
                setTimeout(() => {
                    btn.textContent = 'Αντιγραφή';
                    btn.classList.remove('copied');
                }, 1500);
            });
        });
    });
}

function initSidebarScroll() {
    const links = document.querySelectorAll('.sidebar a');
    if (!links.length) return;

    const entries = [];
    links.forEach(link => {
        const id = link.getAttribute('href')?.slice(1);
        const el = id ? document.getElementById(id) : null;
        if (el) entries.push({ el, link });
    });

    if (!entries.length) return;

    window.addEventListener('scroll', () => {
        let current = entries[0];
        for (const entry of entries) {
            if (entry.el.getBoundingClientRect().top <= 100) {
                current = entry;
            }
        }
        links.forEach(l => l.classList.remove('active'));
        current.link.classList.add('active');
    }, { passive: true });
}
