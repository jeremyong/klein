/*
window.MathJax = {
    options: {
        ignoreHtmlClass: 'tex2jax_ignore',
        processHtmlClass: 'tex2jax_process',
        renderActions: {
            find: [10, function (doc) {
                for (const node of document.querySelectorAll('script[type^="math/tex"]')) {
                    const display = !!node.type.match(/; *mode=display/);
                    const math = new doc.options.MathItem(node.textContent, doc.inputJax[0], display);
                    const text = document.createTextNode('');
                    const sibling = node.previousElementSibling;
                    node.parentNode.replaceChild(text, node);
                    math.start = { node: text, delim: '', n: 0 };
                    math.end = { node: text, delim: '', n: 0 };
                    doc.math.push(math);
                    if (sibling && sibling.matches('.MathJax_Preview')) {
                        sibling.parentNode.removeChild(sibling);
                    }
                }
            }, '']
        }
    },
    tex: {
        autoload: {
            color: [],
            colorV2: ['color']
        },
        packages: { '[+]': ['noerrors'] },
        inlineMath: [["\\(", "\\)"]],
        displayMath: [["\\[", "\\]"]],
        processEscapes: true,
        processEnvironments: true
    },
    loader: {
        load: ['[tex]/noerrors']
    }
};
*/
(function () {
    'use strict';

    var katexMath = (function () {
        var maths = document.querySelectorAll('.arithmatex'),
            tex;

        for (var i = 0; i < maths.length; i++) {
            tex = maths[i].textContent || maths[i].innerText;
            if (tex.startsWith('\\(') && tex.endsWith('\\)')) {
                katex.render(tex.slice(2, -2), maths[i], { 'displayMode': false });
            } else if (tex.startsWith('\\[') && tex.endsWith('\\]')) {
                katex.render(tex.slice(2, -2), maths[i], { 'displayMode': true });
            }
        }
    });

    (function () {
        var onReady = function onReady(fn) {
            if (document.addEventListener) {
                document.addEventListener("DOMContentLoaded", fn);
            } else {
                document.attachEvent("onreadystatechange", function () {
                    if (document.readyState === "interactive") {
                        fn();
                    }
                });
            }
        };

        onReady(function () {
            if (typeof katex !== "undefined") {
                katexMath();
            }
        });
    })();

}());