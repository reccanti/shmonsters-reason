/**
 * This class is used to interact with the canvas
 * component using regular JavaScript and will be
 * wrapped by ReasonReact code 
 */
import React, { useReducer } from "react";
import PropTypes from "prop-types";

const actions = Object.freeze({
    SET_DRAWING_CANVAS: "SET_DRAWING_CANVAS",
    SET_MOUSE_CANVAS: "SET_MOUSE_CANVAS",
    SET_MOUSE_DOWN: "SET_MOUSE_DOWN",
    SET_MOUSE_UP: "SET_MOUSE_UP",
    SET_DATA_URL: "SET_DATA_URL"
});

function updateState(state, action) {
    console.log(state);
    if (action.type === actions.SET_DRAWING_CANVAS && (!state.drawingCanvas || !state.drawingContext)) {
        return {
            ...state,
            drawingCanvas: action.drawingCanvas,
            drawingContext: action.drawingContext
        }
    } else if (action.type === actions.SET_MOUSE_CANVAS && (!state.mouseCanvas || !state.mouseContext)) {
        return {
            ...state,
            mouseCanvas: action.mouseCanvas,
            mouseContext: action.mouseContext
        }
    } else if (action.type === actions.SET_MOUSE_DOWN) {
        return {
            ...state,
            mouseDown: true
        }
    } else if (action.type === actions.SET_MOUSE_UP) {
        return {
            ...state,
            mouseDown: false
        }
    } else if (action.type === actions.SET_DATA_URL) {
        return {
            ...state,
            dataUrl: action.dataUrl
        }
    } else {
        return state;
    }
}

const JsCanvas = ({ width, height, initialDataUrl, onChange }) => {

    const [state, dispatch] = useReducer(updateState, {
        drawingCanvas: null,
        drawingContext: null,
        mouseCanvas: null,
        mouseContext: null,
        mouseDown: false,
        dataUrl: initialDataUrl
    });

    // console.log(state);

    function createDrawingCanvas(element) {
        if (element) {
            const drawingCanvas = element;
            const drawingContext = element.getContext("2d");

            // draw the dataURL provided on the canvas
            const img = new Image();
            img.onload = () => {
                drawingContext.drawImage(img, 0, 0);
            }
            img.src = initialDataUrl;
            dispatch({
                type: actions.SET_DRAWING_CANVAS,
                drawingCanvas,
                drawingContext
            });
        }
    }

    function createMouseCanvas(element) {
        if (element) {
            dispatch({
                type: actions.SET_MOUSE_CANVAS,
                mouseCanvas: element,
                mouseContext: element.getContext("2d")
            });
        }
    }

    function handleMouseMove(event) {
        // create the hover state
        const canvasSize = state.mouseCanvas.getBoundingClientRect();
        const mouseX = Math.floor(((event.clientX - canvasSize.left) / canvasSize.width) * width);
        const mouseY = Math.floor(((event.clientY - canvasSize.top) / canvasSize.height) * height);
        state.mouseContext.clearRect(0, 0, width, height);
        state.mouseContext.fillStyle = "gray";
        state.mouseContext.fillRect(mouseX, mouseY, 1, 1);

        // draw to the canvas below
        if (state.mouseDown) {
            state.drawingContext.fillStyle = "white";
            state.drawingContext.fillRect(mouseX, mouseY, 1, 1);
        }
    }

    function handleMouseDown(event) {
        dispatch({
            type: actions.SET_MOUSE_DOWN
        });
    }

    function handleMouseUp(event) {
        const dataUrl = state.drawingCanvas.toDataURL("image/png");
        dispatch({
            type: actions.SET_MOUSE_UP
        });
        dispatch({
            type: actions.SET_DATA_URL,
            dataUrl
        });
        onChange(dataUrl);
    }

    return (
        <div style={{ position: "relative" }}>
            {/* Mouse canvas */}
            <canvas
                ref={createMouseCanvas}
                style={{ width: "100%", height: "auto", imageRendering: "crisp-edges", position: "absolute" }}
                width={width}
                height={height}
                onMouseMove={handleMouseMove}
                onMouseDown={handleMouseDown}
                onMouseUp={handleMouseUp}
            />
            {/* Image canvas */}
            <canvas
                ref={createDrawingCanvas}
                style={{ width: "100%", height: "auto", imageRendering: "crisp-edges" }}
                width={width}
                height={height}
            />
        </div>
    )
}

JsCanvas.propTypes = {
    width: PropTypes.string.isRequired,
    height: PropTypes.string.isRequired,
    initialDataUrl: PropTypes.string,
    onChange: PropTypes.func
}

JsCanvas.defaultProps = {
    initialDataUrl: "",
    onChange() { },
}

export default JsCanvas;